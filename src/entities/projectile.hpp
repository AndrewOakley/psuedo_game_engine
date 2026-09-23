#pragma once

#include "raylib.h"

namespace entities {
class Projectile {
public:
    explicit Projectile(Vector2 startPosition, Vector2 direction);

    void update(float dt);
    void draw() const;
    void destroy() noexcept;

    [[nodiscard]] const Rectangle& bounds() const noexcept;
    [[nodiscard]] bool isAlive() const noexcept;

private:
    void updateBounds() noexcept;

    Vector2 position_ {};
    Vector2 velocity_ {};
    Rectangle bounds_ {};
    bool alive_ { true };

    static constexpr float kMoveSpeed = 300.0F;
    static constexpr float kSize = 5.0F;
};
}
