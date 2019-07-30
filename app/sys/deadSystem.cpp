//
// Created by baifeng on 2019-07-29.
//

#include "deadSystem.h"
#include <core/context.h>
#include <struct/state.h>
#include <struct/scale.h>
#include <struct/tile.h>
#include <helpers/gemHelper.h>

void updateIndeadGems(context& c, int ms) {
    auto& entity = c.entity;
    float dt = ms / 1000.0f;
    int dead_count = 0;
    entity.view<Indead, Scale>().each([&](auto e, Indead& indead, Scale& scale) {
        bool dead = false;
        scale.x -= dt / 0.3f;
        scale.y -= dt / 0.3f;
        if (scale.x <= 0 && scale.y <= 0) {
            dead = true;
        }
        if (dead) {
            entity.reset<Indead>(e);
            entity.assign<Dead>(e);
            dead_count ++;
        }
    });
    if (dead_count != 0) {
        c.check_link = true;
    }
}

typedef std::vector<entt::entity> gem_array;
typedef std::map<int, gem_array> gem_sets;

void procGemsFall(context& c, gem_sets const& gems) {
    auto& entity = c.entity;
    for (auto iter = gems.begin(); iter != gems.end(); iter++) {
        int hole = 0;
        for (int i = c.level.getMapHeight()-1; i >= 0; i--) {
            auto e = c.level.get(level::TILE, iter->first, i);
            if (e == entt::null) {
                continue;
            }
            if (entity.has<Dead>(e)) {
                hole++;
                continue;
            }
            if (hole != 0) {
                entity.assign_or_replace<Falling>(e);
                entity.assign_or_replace<TileEnd>(e, int(iter->first), i+hole);
            }
        }
    }
}

void procNewGems(context& c, gem_sets const& gems) {
    auto& entity = c.entity;
    for (auto iter = gems.begin(); iter != gems.end(); iter++) {
        for (int i = 0; i < iter->second.size(); ++i) {
            auto id = c.level.makeGemId();
            auto e = createGem(entity, id, Position{
                gems::GEM_WIDTH*0.5f+iter->first*gems::GEM_WIDTH,
                -gems::GEM_HEIGHT*0.5f+i*(-gems::GEM_HEIGHT)
                }, Tile{iter->first, -1-i});
            entity.assign<Falling>(e); // 下降中
            entity.assign<TileEnd>(e, int(iter->first), int(iter->second.size()-i-1));
        }
    }
}

void updateDeadGems(context& c) {
    auto& entity = c.entity;
    std::vector<entt::entity> deadGems;
    // 搜集被消除的宝石
    entity.view<Dead>().each([&](auto e, Dead& dead) {
        deadGems.push_back(e);
    });
    gem_sets list;
    for (int i = 0; i < deadGems.size(); ++i) {
        auto e = deadGems[i];
        auto const& tile = entity.get<Tile>(e);
        list[tile.x].push_back(e);
    }
    // 补充新宝石
    procNewGems(c, list);
    // 下落宝石
    procGemsFall(c, list);
    // 移除被消除的宝石
    for (int i = 0; i < deadGems.size(); ++i) {
        auto e = deadGems[i];
        auto const& tile = entity.get<Tile>(e);
        c.level.set(level::TILE, tile.x, tile.y, entt::null);
        entity.destroy(e);
    }
}