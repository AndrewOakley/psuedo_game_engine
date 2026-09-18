#pragma once

#include "raylib.h"

namespace entities {
class Enemy final {
public:
    explicit Enemy(Vector2 startPosition = { 200.0f, 200.0f });

    void update(float dt);
    void draw() const;
    void destroy() noexcept;

    [[nodiscard]] const Rectangle& bounds() const noexcept;
    [[nodiscard]] bool isAlive() const noexcept;

private:
    void updateBounds() noexcept;

    bool alive_ { true };
    Vector2 position_ {};
    Vector2 velocity_ {};
    Rectangle bounds_ {};
    Vector2 direction_ { 0.0F, -1.0F };
    float directionCooldown_ { 5.0F };
    float directionTimer_ { 0.0F };

    static constexpr float kMoveSpeed = 50.0F;
    static constexpr float kSize = 50.0F;
    static constexpr float kDebugVelocityScale = 0.15F;
};
}
