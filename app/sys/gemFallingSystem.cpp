//
// Created by baifeng on 2019-07-29.
//

#include "gemFallingSystem.h"
#include <core/context.h>
#include <struct/state.h>
#include <struct/position.h>
#include <struct/tile.h>
#include <struct/gem.h>
#include <core/Gems.h>
#include <helpers/gemHelper.h>
#include <sys/checkGemLink.h>
#include <utils/levelUtil.h>

void gemFallingSystem(context& c, int ms) {
    auto& entity = c.entity;
    float dt = ms / 1000.0f;
    entity.view<Gem, Falling, Position, Tile, TileEnd>().each([&](auto e, Gem const& gem, Falling& fall, Position& pos, Tile& tile, TileEnd& end) {
        float end_y = Gems::GEM_HEIGHT * 0.5f + end.y * Gems::GEM_HEIGHT;
        pos.y += 300.0f * (dt / 0.3f);
        if (pos.y >= end_y) {
            Tile temp = tile;
            pos.y = end_y;
            tile.x = end.x;
            tile.y = end.y;
            entity.reset<TileEnd>(e);
            entity.reset<Falling>(e);
        }
    });
    if (entity.size<Falling>() == 0) {
        entity_map entities;
        entities.resize(c.level.getMapWidth());
        entity.view<Gem, Tile>().each([&](auto e, Gem const& gem, Tile const& tile) {
            entities[tile.x].push_back(e);
        });
        auto sort_f = [&](entt::entity e0, entt::entity e1) {
            auto& t0 = entity.get<Tile>(e0);
            auto& t1 = entity.get<Tile>(e1);
            return t0.y < t1.y;
        };
        for (int x = 0; x < entities.size(); ++x) {
            std::sort(entities[x].begin(), entities[x].end(), sort_f);
            for (int y = 0; y < c.level.getMapHeight(); ++y) {
                if (y >= entities[x].size()) {
                    auto e = createGem(entity, 0, Position{
                        Gems::GEM_WIDTH * x + Gems::GEM_WIDTH * 0.5f,
                        Gems::GEM_HEIGHT * y + Gems::GEM_HEIGHT * 0.5f,
                        }, Tile{x, y});
                    entity.assign<Dead>(e);
                    continue;
                }
                auto e = entities[x][y];
                if (!entity.valid(e)) {
                    continue;
                }
                auto& tile = entity.get<Tile>(e);
                //printf("[%d, %d] [%d, %d]\n", x, y, tile.x, tile.y);
                if (tile.y != y) {
                    entity.assign_or_replace<Falling>(e);
                    entity.assign_or_replace<TileEnd>(e, TileEnd{x, y});
                }
            }
        }
    }
}