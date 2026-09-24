#include "entities/apple.hpp"

#include "raymath.h"

namespace entities {
Apple::Apple(Vector2 position)
    : position_(position)
    , bounds_({
        position_.x - (kSize / 2.0F),
        position_.y - (kSize / 2.0F),
        kSize,
        kSize
    }) {}

void Apple::update(float dt) {
    (void)dt;
}

void Apple::draw() const {
    DrawRectangleRec(bounds_, RED);
    DrawRectangleLinesEx(bounds_, 1.0F, BLUE);
    DrawCircleV(position_, 3.0F, BLACK);
}

const Rectangle& Apple::bounds() const noexcept {
    return bounds_;
}

const Vector2& Apple::position() const noexcept {
    return position_;
}

void Apple::setPosition(Vector2 position) {
    position_ = position;
    updateBounds();
}

void Apple::updateBounds() noexcept {
    bounds_ = {
        position_.x - (kSize / 2.0F),
        position_.y - (kSize / 2.0F),
        kSize,
        kSize
    };
}
}
