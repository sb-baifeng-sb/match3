//
// Created by baifeng on 2019-07-28.
//

#include "gemHelper.h"
#include <struct/tile.h>
#include <struct/gem.h>
#include <struct/scale.h>

entt::entity createGem(entt::registry& entity, int id, Position const& pos, Tile const& tile) {
    auto e = entity.create();
    entity.assign<Tile>(e, tile);
    entity.assign<Position>(e, pos);
    entity.assign<Scale>(e, 1.0f, 1.0f);
    entity.assign<Gem>(e, id);
    entity.assign<GemSprite>(e);
    return e;
}
