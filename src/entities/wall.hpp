#pragma once

#include "raylib.h"

namespace entities {
class Wall {
public:
    explicit Wall(Vector2 position, float width, float height);

    void draw() const;

    [[nodiscard]] const Rectangle& bounds() const noexcept;

private:
    Rectangle bounds_ {};
};
}
