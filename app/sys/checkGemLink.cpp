//
// Created by baifeng on 2019-07-29.
//

#include "checkGemLink.h"
#include <core/context.h>
#include <struct/state.h>
#include <struct/tile.h>
#include <struct/gem.h>
#include <utils/levelUtil.h>

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

bool _isLink(context& c, entity_map const& gem_map, entt::entity e, Tile* style, int styleSize) {
    auto& entity = c.entity;
    auto const& tile = entity.get<Tile>(e);
    auto const& id = entity.get<Gem>(e).id;
    int count = 0;
    for (int i = 0; i < styleSize; ++i) {
        auto const& step = style[i];
        int x = tile.x+step.x;
        int y = tile.y+step.y;
        if (x < 0 || x >= c.level.getMapWidth() || y < 0 || y >= c.level.getMapHeight()) {
            continue;
        }
        auto next = gem_map[x][y];
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

void _setLink(context& c, entity_map const& gem_map, entt::entity e, Tile* style, int styleSize) {
    auto& entity = c.entity;
    auto const& tile = entity.get<Tile>(e);
    for (int i = 0; i < styleSize; ++i) {
        auto const& step = style[i];
        int x = tile.x+step.x;
        int y = tile.y+step.y;
        if (x < 0 || x >= c.level.getMapWidth() || y < 0 || y >= c.level.getMapHeight()) {
            continue;
        }
        auto next = gem_map[x][y];
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
    if (entity.size<Falling>() != 0) {
        return;
    }
    if (!c.check_link) {
        return;
    }
    c.check_link = false;
    auto gem_map = getLevelGemMap(c);
    for (int x = 0; x < c.level.getMapWidth(); ++x) {
        for (int y = 0; y < c.level.getMapHeight(); ++y) {
            auto e = gem_map[x][y];
            if (e == entt::null) {
                continue;
            }
            if (_isLink(c, gem_map, e, _link0, 3)) {
                _setLink(c, gem_map, e, _link0, 3);
            }
            if (_isLink(c, gem_map, e, _link1, 3)) {
                _setLink(c, gem_map, e, _link1, 3);
            }
        }
    }
    entity.view<Linked>().each([&](auto e, Linked const& l) {
        entity.reset<Linked>(e);
        entity.assign<Indead>(e);
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
    auto gem_map = getLevelGemMap(c);
    entity.view<GemSwapFinish, Tile, TileEnd>().each([&](auto e, GemSwapFinish const& finish, Tile const& tile, TileEnd const& end) {
        for (int i = 0; i < 5; ++i) {
            auto& curr = _swapCheckLink[i];
            int x = tile.x + curr.x;
            int y = tile.y + curr.y;
            if (x < 0 || x >= c.level.getMapWidth() || y < 0 || y >= c.level.getMapHeight()) {
                continue;
            }
            auto next = gem_map[x][y];
            if (next == entt::null) {
                continue;
            }
            if (_isLink(c, gem_map, next, _link0, 3)) {
                has_link = true;
            } else if (_isLink(c, gem_map, next, _link1, 3)) {
                has_link = true;
            }
            if (has_link) {
                c.check_link = true;
                break;
            }
        }
    });
    if (entity.size<GemSwaping>() != 0) {
        return;
    }
    if (c.check_link) {
        entity.view<GemSwapFinish, TileEnd>().each([&](auto e, GemSwapFinish const& finish, TileEnd const& end) {
            entity.reset<GemSwapFinish>(e);
            entity.reset<TileEnd>(e);
        });
        return;
    }
    // 还原宝石位置
    entity.view<GemSwapFinish, Tile, TileEnd>().each([&](auto e, GemSwapFinish const& finish, Tile const& tile, TileEnd const& end) {
        entity.reset<GemSwapFinish>(e);
        entity.assign_or_replace<GemReverseSwaping>(e);
    });
}