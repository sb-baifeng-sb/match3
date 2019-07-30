//
// Created by baifeng on 2019-07-29.
//

#include "checkGemLink.h"
#include <core/context.h>
#include <struct/state.h>
#include <struct/tile.h>
#include <struct/gem.h>

// 横3个
static Tile _link0[3] = {
        {-1, 0},
        {0, 0},
        {1, 0}
};

// 竖3个
static Tile _link1[3] = {
        {0, -1},
        {0, 0},
        {0, 1},
};

bool _isLink(context& c, entt::entity e, Tile* style, int styleSize) {
    auto& entity = c.entity;
    auto const& tile = entity.get<Tile>(e);
    auto const& id = entity.get<Gem>(e).id;
    int count = 0;
    for (int i = 0; i < styleSize; ++i) {
        auto const& step = style[i];
        auto next = c.level.get(Level::TILE, tile.x + step.x, tile.y + step.y);
        if (next == entt::null) {
            continue;
        }
        if (entity.has<Falling>(next) || entity.has<Indead>(next)) {
            continue;
        }
        if (id == entity.get<Gem>(next).id) {
            count ++;
        }
    }
    return count == styleSize;
}

void _setLink(context& c, entt::entity e, Tile* style, int styleSize) {
    auto& entity = c.entity;
    auto const& tile = entity.get<Tile>(e);
    for (int i = 0; i < styleSize; ++i) {
        auto const& step = style[i];
        auto next = c.level.get(Level::TILE, tile.x + step.x, tile.y + step.y);
        if (next == entt::null) {
            continue;
        }
        if (entity.has<Linked>(next)) {
            continue;
        }
        entity.assign<Linked>(next);
    }
}

void checkGemLink(context& c) {
    auto& entity = c.entity;
    for (int x = 0; x < c.level.getMapWidth(); ++x) {
        for (int y = 0; y < c.level.getMapHeight(); ++y) {
            auto e = c.level.get(Level::TILE, x, y);
            if (e == entt::null) {
                continue;
            }
            if (_isLink(c, e, _link0, 3)) {
                _setLink(c, e, _link0, 3);
            } else if (_isLink(c, e, _link1, 3)) {
                _setLink(c, e, _link1, 3);
            }
        }
    }
    entity.view<Linked>().each([&](auto e, Linked& link) {
        entity.reset<Linked>(e);
        entity.assign_or_replace<Indead>(e);
    });
}

static Tile _swapCheckLink[5] = {
        {-1, 0},
        {1, 0},
        {0, 0},
        {0, -1},
        {0, 1},
};

void checkSwapGemLink(context& c) {
    auto& entity = c.entity;
    bool has_link = false;

    entity.view<GemSwapFinish, Tile, TileEnd>().each([&](auto e, GemSwapFinish const& finish, Tile const& tile, TileEnd const& end) {
        for (int i = 0; i < 5; ++i) {
            auto& curr = _swapCheckLink[i];
            auto next = c.level.get(Level::TILE, tile.x + curr.x, tile.y + curr.y);
            if (next == entt::null) {
                continue;
            }
            if (_isLink(c, next, _link0, 3)) {
                has_link = true;
            } else if (_isLink(c, next, _link1, 3)) {
                has_link = true;
            }
            if (has_link) {
                break;
            }
        }
    });
    if (has_link) {
        return;
    }
    // 还原宝石位置
    entity.view<GemSwapFinish, Tile, TileEnd>().each([&](auto e, GemSwapFinish const& finish, Tile const& tile, TileEnd const& end) {
        entity.reset<GemSwapFinish>(e);
        entity.assign_or_replace<GemReverseSwaping>(e);
    });
}