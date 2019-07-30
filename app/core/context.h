//
// Created by baifeng on 2019-07-28.
//

#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include <core/level.h>
#include <core/render.h>
#include <core/input.h>
#include <core/gems.h>

class context {
public:
    entt::registry entity;
    level level;
    gems gems;
    input input;
    render render;
    bool check_link;
};

#endif //APP_CONTEXT_H
