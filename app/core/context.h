//
// Created by baifeng on 2019-07-28.
//

#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include <core/Level.h>
#include <core/Render.h>
#include <core/Input.h>
#include <core/Gems.h>

class context {
public:
    entt::registry entity;
    Level level;
    Gems gems;
    Input input;
    Render render;
    bool check_link;
};

#endif //APP_CONTEXT_H
