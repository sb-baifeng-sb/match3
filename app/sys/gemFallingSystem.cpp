//
// Created by baifeng on 2019-07-29.
//

#include "gemFallingSystem.h"
#include <core/context.h>
#include <struct/state.h>
#include <struct/position.h>
#include <struct/tile.h>
#include <core/Gems.h>
#include <sys/checkGemLink.h>

void gemFallingSystem(context& c, int ms) {
    auto& entity = c.entity;
    int falling_count = 0;
    float dt = ms / 1000.0f;
    entity.view<Falling, Position, Tile, TileEnd>().each([&](auto e, Falling& fall, Position& pos, Tile& tile, TileEnd& end) {
        float end_y = Gems::GEM_HEIGHT * 0.5f + end.y * Gems::GEM_HEIGHT;
        pos.y += 300.0f * (dt / 0.3f);
        if (pos.y >= end_y) {
            pos.y = end_y;
            tile.x = end.x;
            tile.y = end.y;
            entity.reset<TileEnd>(e);
            entity.reset<Falling>(e);
            c.level.set(Level::TILE, tile.x, tile.y, e);
        }
        falling_count++;
    });
    if (falling_count == 0 && c.check_link) {
        c.check_link = false;
        checkGemLink(c);
    }
}