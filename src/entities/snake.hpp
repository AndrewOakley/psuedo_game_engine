#pragma once

#include <queue>

#include "raylib.h"

namespace entities {
class Snake final {
public:
    explicit Snake(Vector2 startPosition = { 255.0f, 195.0f });
    void draw() const;
    void resolveCollision(const Rectangle& otherBounds) noexcept;

    [[nodiscard]] const Rectangle& bounds() const noexcept;
    [[nodiscard]] const Vector2& position() const noexcept;

private:
    Vector2 position_;
    Vector2 velocity_ { 1, 0 };
    Rectangle bounds_ {};

    static constexpr float kSize = 30.0F;
};

class SnakeChain final {
public:
    explicit SnakeChain(Vector2 startPosition = { 255.0f, 195.0f });
    void update(float dt);
    void draw() const;
    void addChain() noexcept;
    void setIsAlive(bool val) noexcept;
    bool anyCollision(const Rectangle& otherBounds) const noexcept;

    [[nodiscard]] const Rectangle& bounds() const noexcept;
    [[nodiscard]] bool isAlive() const noexcept;

private:
    std::queue<Snake> chain_{};
    Vector2 velocity_ { 1, 0 };
    bool addChain_ { false };
    bool isAlive_ { true };
    float moveCooldown_ { 0.15f };
    float moveTimer_ { 0.0f };

    static constexpr float kMoveSpeed = 30;
};
}
