#pragma once

#include "raylib.h"

namespace entities {
class Enemy final {
public:
    explicit Enemy(Vector2 startPosition = { 200.0f, 200.0f });

    void update(float dt, Vector2 targetPosition);
    void draw() const;
    void destroy() noexcept;

    [[nodiscard]] const Rectangle& bounds() const noexcept;
    [[nodiscard]] bool isAlive() const noexcept;

    [[nodiscard]] bool damagesPlayer() noexcept;
    void resetPlayerDamage() noexcept;

private:
    void updateBounds() noexcept;

    bool alive_ { true };
    Vector2 position_ {};
    Vector2 velocity_ {};
    Rectangle bounds_ {};
    bool hasDamagedPlayer_ { false };

    static constexpr float kMoveSpeed = 50.0F;
    static constexpr float kSize = 50.0F;
    static constexpr float kDebugVelocityScale = 0.15F;
};
}
