#include "entities/wall.hpp"

namespace entities {
Wall::Wall(Vector2 position, float width, float height)
    : bounds_ { position.x, position.y, width, height } {
}

void Wall::draw() const {
    DrawRectangleRec(bounds_, BLACK);
}

const Rectangle& Wall::bounds() const noexcept {
    return bounds_;
}
}
