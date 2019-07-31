//
// Created by baifeng on 2019-07-30.
//

#include "inputSystem.h"
#include <stdio.h>
#include <core/context.h>
#include <struct/gem.h>
#include <struct/state.h>
#include <helpers/gemHelper.h>
#include <utils/levelUtil.h>

void onMousePressed(context& c, int x, int y) {
    auto& entity = c.entity;
    int tile_x = x / Gems::GEM_WIDTH;
    int tile_y = y / Gems::GEM_HEIGHT;
    auto gem_map = getLevelGemMap(c);
    auto e = gem_map[tile_x][tile_y];
    if (e == entt::null) {
        return;
    }
    entity.assign_or_replace<GemSwapStandby>(e);
}

void onMouseMoved(context& c, int x, int y) {
    auto& entity = c.entity;

    int tile_x = x / Gems::GEM_WIDTH;
    int tile_y = y / Gems::GEM_HEIGHT;
    auto gem_map = getLevelGemMap(c);
    entity.view<GemSwapStandby, Tile>().each([&](auto e, GemSwapStandby const& standby, Tile const& tile) {

        auto next = gem_map[tile_x][tile_y];
        if (next == entt::null) {
            return;
        }
        bool can_swap = false;
        if (tile_x == tile.x && abs(tile_y-tile.y) == 1) {
            can_swap = true;
        } else if (tile_y == tile.y && abs(tile_x-tile.x) == 1) {
            can_swap = true;
        }
        if (!can_swap) {
            return;
        }
        if (entity.has<Falling>(next) || entity.has<Falling>(e)) {
            return;
        }
        if (entity.has<Indead>(next) || entity.has<Indead>(e)) {
            return;
        }
        if (entity.has<GemSwaping>(next) || entity.has<GemSwaping>(e)) {
            return;
        }
        if (entity.has<GemReverseSwaping>(next) || entity.has<GemReverseSwaping>(e)) {
            return;
        }

        entity.reset<GemSwapStandby>(e);
        entity.assign_or_replace<TileEnd>(e, TileEnd{tile_x, tile_y});
        entity.assign<GemSwaping>(e);

        entity.reset<GemSwapStandby>(next);
        entity.assign_or_replace<TileEnd>(next, TileEnd{tile.x, tile.y});
        entity.assign<GemSwaping>(next);
    });
}

void onMouseReleased(context& c, int x, int y) {
    auto& entity = c.entity;
    entity.view<GemSwapStandby, GemSprite>().each([&](auto e, GemSwapStandby const& standby, GemSprite& sprite) {
        entity.reset<GemSwapStandby>(e);
        sprite.index = 0;
        sprite.step = 0;
    });
}