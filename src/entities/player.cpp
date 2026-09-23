#include "entities/player.hpp"

#include "raymath.h"

#include "input/input.hpp"

namespace entities {
Player::Player(Vector2 startPosition)
    : position_(startPosition) {
    updateBounds();
}

void Player::update(float dt) {
    const Vector2 inputDirection {
        static_cast<float>(input::isDown(input::Key::D)) - static_cast<float>(input::isDown(input::Key::A)),
        static_cast<float>(input::isDown(input::Key::S)) - static_cast<float>(input::isDown(input::Key::W))
    };

    velocity_ = Vector2Scale(Vector2Normalize(inputDirection), kMoveSpeed);
    position_ = Vector2Add(position_, Vector2Scale(velocity_, dt));
    updateBounds();
}

void Player::draw() const {
    DrawRectangleRec(bounds_, RED);
    DrawRectangleLinesEx(bounds_, 1.0F, BLUE);
    DrawCircleV(position_, 3.0F, BLACK);
    DrawLineV(position_, Vector2Add(position_, Vector2Scale(velocity_, kDebugVelocityScale)), DARKGREEN);
}

const Rectangle& Player::bounds() const noexcept {
    return bounds_;
}

const Vector2& Player::position() const noexcept {
    return position_;
}

int Player::health() const noexcept {
    return health_;
}

bool Player::isAlive() const noexcept {
    return health_ > 0;
}

void Player::resolveCollision(const Rectangle& otherBounds) noexcept {
    const Rectangle overlap = GetCollisionRec(bounds_, otherBounds);
    if (overlap.width <= 0.0F || overlap.height <= 0.0F) {
        return;
    }

    const float playerCenterX = bounds_.x + (bounds_.width * 0.5F);
    const float playerCenterY = bounds_.y + (bounds_.height * 0.5F);
    const float otherCenterX = otherBounds.x + (otherBounds.width * 0.5F);
    const float otherCenterY = otherBounds.y + (otherBounds.height * 0.5F);

    if (overlap.width < overlap.height) {
        position_.x += playerCenterX < otherCenterX ? -overlap.width : overlap.width;
    } else {
        position_.y += playerCenterY < otherCenterY ? -overlap.height : overlap.height;
    }

    updateBounds();
}

void Player::takeDamage() noexcept {
    if (health_ > 0) {
        --health_;
    }
}

void Player::updateBounds() noexcept {
    bounds_ = {
        position_.x - (kSize / 2.0F),
        position_.y - (kSize / 2.0F),
        kSize,
        kSize
    };
}
}
