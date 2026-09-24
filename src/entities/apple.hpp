#pragma once

#include "raylib.h"

namespace entities {
class Apple final {
public:
    explicit Apple(Vector2 position = { 555.0f, 195.0f });
    void update(float dt);
    void draw() const;
    void setPosition(Vector2 position);
    void updateBounds() noexcept;

    [[nodiscard]] const Rectangle& bounds() const noexcept;
    [[nodiscard]] const Vector2& position() const noexcept;

private:
    Vector2 position_;
    Rectangle bounds_ {};

    static constexpr float kSize = 30.0F;
};
}