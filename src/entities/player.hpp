#pragma once

#include "raylib.h"

namespace entities {
class Player final {
public:
    explicit Player(Vector2 startPosition = { 200.0f, 200.0f });
    void update(float dt);
    void draw() const;
    void resolveCollision(const Rectangle& otherBounds) noexcept;
    void takeDamage() noexcept;

    [[nodiscard]] const Rectangle& bounds() const noexcept;
    [[nodiscard]] const Vector2& position() const noexcept;
    [[nodiscard]] int health() const noexcept;
    [[nodiscard]] bool isAlive() const noexcept;

private:
    void updateBounds() noexcept;

    Vector2 position_;
    Vector2 velocity_ {};
    Rectangle bounds_ {};
    int health_ { kStartingHealth };

    static constexpr int kStartingHealth = 5;
    static constexpr float kMoveSpeed = 200.0F;
    static constexpr float kSize = 30.0F;
    static constexpr float kDebugVelocityScale = 0.15F;
};
}
