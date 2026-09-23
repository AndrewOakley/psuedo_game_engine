#include "entities/enemy.hpp"
#include "raymath.h"

namespace entities {
Enemy::Enemy(Vector2 startPosition)
    : position_(startPosition) {
    updateBounds();
}

void Enemy::update(float dt, Vector2 targetPosition) {
    if (!alive_) {
        return;
    }

    const Vector2 direction = Vector2Subtract(targetPosition, position_);

    velocity_ = Vector2Scale(Vector2Normalize(direction), kMoveSpeed);
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

bool Enemy::isAlive() const noexcept {
    return alive_;
}

void Enemy::destroy() noexcept {
    alive_ = false;
}

bool Enemy::damagesPlayer() noexcept {
    if (hasDamagedPlayer_) {
        return false;
    }

    hasDamagedPlayer_ = true;
    return true;
}

void Enemy::resetPlayerDamage() noexcept {
    hasDamagedPlayer_ = false;
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
