#include "entities/projectile.hpp"

#include "raymath.h"

namespace entities {
Projectile::Projectile(Vector2 startPosition, Vector2 direction)
    : position_(startPosition)
    , velocity_(Vector2Scale(Vector2Normalize(direction), kMoveSpeed)) {
    updateBounds();
}

void Projectile::update(float dt) {
    position_ = Vector2Add(position_, Vector2Scale(velocity_, dt));
    updateBounds();
}

void Projectile::draw() const {
    DrawRectangleRec(bounds_, RED);
    DrawRectangleLinesEx(bounds_, 1.0F, BLUE);
    DrawCircleV(position_, 3.0F, BLACK);
}

void Projectile::destroy() noexcept {
    alive_ = false;
}

const Rectangle& Projectile::bounds() const noexcept {
    return bounds_;
}

bool Projectile::isAlive() const noexcept {
    return alive_;
}

void Projectile::updateBounds() noexcept {
    bounds_ = {
        position_.x - (kSize / 2.0F),
        position_.y - (kSize / 2.0F),
        kSize,
        kSize
    };
}
}
