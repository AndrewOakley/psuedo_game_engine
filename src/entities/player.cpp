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

void Player::updateBounds() noexcept {
    bounds_ = {
        position_.x - (kSize / 2.0F),
        position_.y - (kSize / 2.0F),
        kSize,
        kSize
    };
}
}
