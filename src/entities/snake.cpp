#include "entities/snake.hpp"

#include "raymath.h"

#include "input/input.hpp"

namespace entities {
Snake::Snake(Vector2 startPosition)
    : position_(startPosition)
    , bounds_({
        position_.x - (kSize / 2.0F),
        position_.y - (kSize / 2.0F),
        kSize,
        kSize
    }) {}

void Snake::draw() const {
    DrawRectangleRec(bounds_, GREEN);
    DrawRectangleLinesEx(bounds_, 1.0F, BLUE);
    DrawCircleV(position_, 3.0F, BLACK);
}

const Rectangle& Snake::bounds() const noexcept {
    return bounds_;
}

const Vector2& Snake::position() const noexcept {
    return position_;
}

// chain
SnakeChain::SnakeChain(Vector2 startPosition) {
    chain_.emplace(startPosition);
}

void SnakeChain::update(float dt) {
    Vector2 direction = velocity_;
    if (input::wasPressed(input::Key::D) && direction.x == 0) {
        direction = { 1, 0 };
    } else if (input::wasPressed(input::Key::A) && direction.x == 0) {
        direction = { -1, 0 };
    } else if (input::wasPressed(input::Key::W) && direction.y == 0) {
        direction = { 0, -1 };
    } else if (input::wasPressed(input::Key::S) && direction.y == 0) {
        direction = { 0, 1 };
    }
    velocity_ = Vector2Scale(Vector2Normalize(direction), kMoveSpeed);

    moveTimer_ += dt;
    if (moveTimer_ >= moveCooldown_) {
        moveTimer_ = 0.0f;
    } else {
        return;
    }

    Vector2 nextPos = Vector2Add(chain_.back().position(), velocity_);
    chain_.emplace(nextPos);
    if (addChain_) {
        addChain_ = false;
    } else {
        chain_.pop();
    }

    std::queue<Snake> tempChain_ = chain_;

    while (!tempChain_.empty()) {
        if (tempChain_.size() == 1) return;

        if (CheckCollisionRecs(tempChain_.front().bounds(), tempChain_.back().bounds())) {
            setIsAlive(false);
            return;
        }

        tempChain_.pop(); 
    }
}

void SnakeChain::draw() const {
    std::queue<Snake> tempChain_ = chain_;

    while (!tempChain_.empty()) {
        tempChain_.front().draw();
        tempChain_.pop(); 
    }
}

void SnakeChain::setIsAlive(bool val) noexcept {
    isAlive_ = val;
}

bool SnakeChain::isAlive() const noexcept {
    return isAlive_;
}

void SnakeChain::addChain() noexcept {
    addChain_ = true;
}

const Rectangle& SnakeChain::bounds() const noexcept {
    return chain_.back().bounds();
}

bool SnakeChain::anyCollision(const Rectangle& otherBounds) const noexcept {
    std::queue<Snake> tempChain_ = chain_;

    while (!tempChain_.empty()) {
        if (CheckCollisionRecs(tempChain_.front().bounds(), otherBounds)) {
            return true;
        }

        tempChain_.pop(); 
    }

    return false;
}
}
