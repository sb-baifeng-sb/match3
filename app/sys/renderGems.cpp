//
// Created by baifeng on 2019-07-29.
//

#include "renderGems.h"
#include <core/context.h>
#include <struct/gem.h>
#include <struct/position.h>
#include <struct/scale.h>

void renderGems(context& c) {
    auto& entity = c.entity;
    entity.view<Gem, Position, Scale, GemSprite>().each([&](auto e, Gem& gem, Position& pos, Scale& scale, GemSprite& sp) {
        auto& sprite = c.gems.getSprite();
        auto& rect = c.gems.getGemFrame(gem.id, sp.index);
        sprite.setScale(scale.x, scale.y);
        sprite.setPosition(pos.x, pos.y);
        sprite.setTextureRect(rect);
        c.render.draw(sprite);
    });
}
