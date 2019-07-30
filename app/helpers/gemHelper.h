//
// Created by baifeng on 2019-07-28.
//

#ifndef APP_GEMHELPER_H
#define APP_GEMHELPER_H

#include <entt/entt.hpp>
#include <struct/position.h>
#include <struct/tile.h>

entt::entity createGem(entt::registry& entity, int id, Position const& pos, Tile const& tile);

#endif //APP_GEMHELPER_H
