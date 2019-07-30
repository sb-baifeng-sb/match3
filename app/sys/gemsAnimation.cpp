//
// Created by baifeng on 2019-07-30.
//

#include "gemsAnimation.h"
#include <core/context.h>
#include <struct/gem.h>
#include <struct/state.h>

void updateGemsSelectAni(context& c, int ms) {
    auto& entity = c.entity;
    entity.view<GemSwapStandby, GemSprite>().each([&](auto e, GemSwapStandby const& standby, GemSprite& sprite) {
        sprite.step += ms;
        if (sprite.step >= 200) {
            sprite.step = 0;
            sprite.index = ++sprite.index >= gems::INDEX_MAX ? 0 : sprite.index;
        }
    });
    entity.view<GemSwapFinish, GemSprite>().each([&](auto e, GemSwapFinish const& standby, GemSprite& sprite) {
        sprite.index = 0;
        sprite.step = 0;
    });
}
