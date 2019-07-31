//
// Created by baifeng on 2019-07-31.
//

#include "levelUtil.h"
#include <struct/gem.h>
#include <struct/tile.h>
#include <core/context.h>
#include <struct/state.h>
#include <assert.h>

entity_map getLevelGemMap(context& c) {
    entity_map result;
    result.resize(c.level.getMapWidth());
    for (int x = 0; x < c.level.getMapWidth(); ++x) {
        result[x].resize(c.level.getMapHeight(), entt::null);
    }
    auto& entity = c.entity;
    entity.view<Gem, Tile>().each([&](auto e, Gem const& gem, Tile const& tile) {
        if (tile.x < 0 || tile.x >= c.level.getMapWidth() || tile.y < 0 || tile.y >= c.level.getMapHeight()) {
            return;
        }
        if (!entity.valid(e)) {
            return;
        }
        if (entity.has<Falling>(e) || entity.has<Indead>(e)) {
            return;
        }
        if (entity.has<GemSwaping>(e) || entity.has<GemReverseSwaping>(e)) {
            return;
        }
        result[tile.x][tile.y] = e;
    });
    return result;
}