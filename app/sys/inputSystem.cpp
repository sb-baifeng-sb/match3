//
// Created by baifeng on 2019-07-30.
//

#include "inputSystem.h"
#include <stdio.h>
#include <core/context.h>
#include <struct/gem.h>
#include <struct/state.h>
#include <helpers/gemHelper.h>

void onMousePressed(context& c, int x, int y) {
    int tile_x = x / gems::GEM_WIDTH;
    int tile_y = y / gems::GEM_HEIGHT;
    auto& entity = c.entity;
    auto e = c.level.get(level::TILE, tile_x, tile_y);
    if (e == entt::null) {
        return;
    }
    if (entity.has<GemSwaping>(e) or entity.has<GemReverseSwaping>(e) or entity.has<Indead>(e) or entity.has<Falling>(e)) {
        return;
    }
    entity.assign_or_replace<GemSwapStandby>(e);
}

void onMouseMoved(context& c, int x, int y) {
    int tile_x = x / gems::GEM_WIDTH;
    int tile_y = y / gems::GEM_HEIGHT;
    auto& entity = c.entity;
    entity.view<GemSwapStandby, Tile>().each([&](auto e, GemSwapStandby const& standby, Tile const& tile) {

        auto next = c.level.get(level::TILE, tile_x, tile_y);
        if (next == entt::null) {
            return;
        }
        if (entity.has<GemSwaping>(next) or entity.has<GemReverseSwaping>(next) or entity.has<Indead>(next) or entity.has<Falling>(e)) {
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
    entity.view<GemSwapStandby>().each([&](auto e, GemSwapStandby const& standby) {
        entity.reset<GemSwapStandby>(e);
        entity.assign_or_replace<GemSwapFinish>(e);
    });
}