#include "entities/enemy.hpp"

#include "raymath.h"

namespace entities {
Enemy::Enemy(Vector2 startPosition)
    : position_(startPosition) {
    updateBounds();
}

void Enemy::update(float dt) {
    directionTimer_ += dt;
    while (directionTimer_ >= directionCooldown_) {
        directionTimer_ -= directionCooldown_;
        direction_.x *= -1.0F;
    }

    velocity_ = Vector2Scale(direction_, kMoveSpeed);
    position_ = Vector2Add(position_, Vector2Scale(velocity_, dt));
    updateBounds();
}

void Enemy::draw() const {
    DrawRectangleRec(bounds_, GREEN);
    DrawRectangleLinesEx(bounds_, 1.0F, BLUE);
    DrawCircleV(position_, 3.0F, BLACK);
    DrawLineV(position_, Vector2Add(position_, Vector2Scale(velocity_, kDebugVelocityScale)), DARKGREEN);
}

const Rectangle& Enemy::bounds() const noexcept {
    return bounds_;
}

void Enemy::updateBounds() noexcept {
    bounds_ = {
        position_.x - (kSize / 2.0F),
        position_.y - (kSize / 2.0F),
        kSize,
        kSize
    };
}
}
