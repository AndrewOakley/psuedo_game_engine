#pragma once

#include "raylib.h"

namespace entities {
class Enemy {
public:
    explicit Enemy(Vector2 startPosition = { 200.0f, 200.0f });

    void update(float dt);
    void draw() const;

    [[nodiscard]] const Rectangle& bounds() const noexcept;

private:
    void updateBounds() noexcept;

    Vector2 position_ {};
    Vector2 velocity_ {};
    Rectangle bounds_ {};
    Vector2 direction_ { 1.0F, 0.0F };
    float directionCooldown_ { 3.0F };
    float directionTimer_ { 0.0F };

    static constexpr float kMoveSpeed = 50.0F;
    static constexpr float kSize = 50.0F;
    static constexpr float kDebugVelocityScale = 0.15F;
};
}
