#pragma once

#include "raylib.h"

namespace input {
    enum class Key { W, A, S, D, SPACE };
    enum class MouseButton { LEFT, RIGHT, MIDDLE };

    bool isDown(Key key);
    bool wasPressed(Key key);
    bool wasReleased(Key key);

    bool isDown(MouseButton mouseButton);
    bool wasPressed(MouseButton mouseButton);

    Vector2 mousePosition();
    Vector2 mouseDelta();
    float mouseWheelDelta();
}