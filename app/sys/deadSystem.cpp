//
// Created by baifeng on 2019-07-29.
//

#include "deadSystem.h"
#include <core/context.h>
#include <struct/state.h>
#include <struct/scale.h>
#include <struct/tile.h>
#include <struct/gem.h>
#include <helpers/gemHelper.h>
#include <utils/levelUtil.h>

void updateIndeadGems(context& c, int ms) {
    auto& entity = c.entity;
    float dt = ms / 1000.0f;
    entity.view<Gem, Indead, Scale>().each([&](auto e, Gem const& gem, Indead const& indead, Scale& scale) {
        bool dead = false;
        scale.x -= dt / 0.3f;
        scale.y -= dt / 0.3f;
        if (scale.x <= 0 && scale.y <= 0) {
            dead = true;
        }
        if (dead) {
            entity.reset<Indead>(e);
            entity.assign<Dead>(e);
        }
    });
}

void updateDeadGems(context& c) {
    auto& entity = c.entity;
    if (entity.size<Indead>() != 0) {
        return;
    }
    if (entity.size<Dead>() != 0) {
        c.check_link = true;
        // 设置下落的宝石
        auto gem_map = getLevelGemMap(c);
        for (int x = 0; x < c.level.getMapWidth(); ++x) {
            int hole = 0;
            for (int y = c.level.getMapHeight() - 1; y >= 0; --y) {
                auto e = gem_map[x][y];
                if (e == entt::null) {
                    continue;
                }
                if (entity.has<Dead>(e)) {
                    hole ++;
                    continue;
                }
                if (hole != 0) {
                    // 往下掉落n格
                    Tile& tile = entity.get<Tile>(e);
                    entity.assign_or_replace<TileEnd>(e, TileEnd{tile.x, tile.y+hole});
                    entity.assign<Falling>(e);
                }
            }
            // 新增n个宝石
            for (int i = 0; i < hole; ++i) {
                int y = hole-i-1;
                auto e = createGem(entity, c.level.makeGemId(), Position{
                    x * Gems::GEM_WIDTH + Gems::GEM_WIDTH * 0.5f,
                    (-i-1) * Gems::GEM_HEIGHT + Gems::GEM_HEIGHT * 0.5f
                    }, Tile{x, -i-1});
                entity.assign<Falling>(e);
                entity.assign<TileEnd>(e, TileEnd{x, y});
            }
        }
    }

    //printf("entity num: %d\n", entity.alive());
    entity.view<Gem, Dead>().each([&](auto e, Gem const& gem, Dead const& dead) {
        entity.destroy(e);
    });
}