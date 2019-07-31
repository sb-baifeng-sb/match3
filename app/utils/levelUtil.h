//
// Created by baifeng on 2019-07-31.
//

#ifndef APP_LEVELUTIL_H
#define APP_LEVELUTIL_H

#include <vector>
#include <entt/entt.hpp>

typedef std::vector<entt::entity> entity_arr;
typedef std::vector<entity_arr> entity_map;

class context;
entity_map getLevelGemMap(context& c);

#endif //APP_LEVELUTIL_H
