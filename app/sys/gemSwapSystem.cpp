//
// Created by baifeng on 2019-07-30.
//

#include <core/context.h>
#include "gemSwapSystem.h"
#include <struct/gem.h>
#include <struct/state.h>
#include <struct/position.h>

void updateGemSwap(context& c, int ms) {
    auto& entity = c.entity;
    float dt = ms / 1000.0f;
    entity.view<GemSwaping, Position, Tile, TileEnd>().each([&](auto e, GemSwaping const& swaping, Position& pos, Tile& tile, TileEnd& end) {
        float end_x = end.x * Gems::GEM_WIDTH + Gems::GEM_WIDTH * 0.5f;
        float end_y = end.y * Gems::GEM_HEIGHT + Gems::GEM_HEIGHT * 0.5f;
        float v = 100.0f * (dt / 0.3f);
        float x_ok = false, y_ok = false;

        if (end.x > tile.x) {
            // 往右移动
            pos.x += v;
            if (pos.x >= end_x) {
                pos.x = end_x;
                x_ok = true;
            }
        } else if (end.x < tile.x) {
            // 往左移动
            pos.x -= v;
            if (pos.x <= end_x) {
                pos.x = end_x;
                x_ok = true;
            }
        }
        if (end.y > tile.y) {
            // 往下移动
            pos.y += v;
            if (pos.y >= end_y) {
                pos.y = end_y;
                y_ok = true;
            }
        } else if (end.y < tile.y) {
            // 往上移动
            pos.y -= v;
            if (pos.y <= end_y) {
                pos.y = end_y;
                y_ok = true;
            }
        }

        if (x_ok or y_ok) {
            // 移动完成
            Tile temp = tile;
            tile.x = end.x; tile.y = end.y;
            end.x = temp.x; end.y = temp.y;
            entity.reset<GemSwaping>(e);
            entity.assign_or_replace<GemSwapFinish>(e);
        }
    });
}

void updateGemSwapReverse(context& c, int ms) {
    auto& entity = c.entity;
    float dt = ms / 1000.0f;
    entity.view<GemReverseSwaping, Position, Tile, TileEnd>().each([&](auto e, GemReverseSwaping const& swaping, Position& pos, Tile& tile, TileEnd& end) {
        float end_x = end.x * Gems::GEM_WIDTH + Gems::GEM_WIDTH * 0.5f;
        float end_y = end.y * Gems::GEM_HEIGHT + Gems::GEM_HEIGHT * 0.5f;
        float v = 100.0f * (dt / 0.3f);
        float x_ok = false, y_ok = false;

        if (end.x > tile.x) {
            // 往右移动
            pos.x += v;
            if (pos.x >= end_x) {
                pos.x = end_x;
                x_ok = true;
            }
        } else if (end.x < tile.x) {
            // 往左移动
            pos.x -= v;
            if (pos.x <= end_x) {
                pos.x = end_x;
                x_ok = true;
            }
        }
        if (end.y > tile.y) {
            // 往下移动
            pos.y += v;
            if (pos.y >= end_y) {
                pos.y = end_y;
                y_ok = true;
            }
        } else if (end.y < tile.y) {
            // 往上移动
            pos.y -= v;
            if (pos.y <= end_y) {
                pos.y = end_y;
                y_ok = true;
            }
        }

        if (x_ok or y_ok) {
            // 移动完成
            Tile temp = tile;
            tile.x = end.x; tile.y = end.y;
            end.x = temp.x; end.y = temp.y;
            entity.reset<GemReverseSwaping>(e);
            entity.reset<TileEnd>(e);
        }
    });
}
