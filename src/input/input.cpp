#include "input.hpp"

namespace {
    KeyboardKey toRaylibKey(input::Key key) {
        switch (key) {
            case input::Key::W:     return KEY_W;
            case input::Key::A:     return KEY_A;
            case input::Key::S:     return KEY_S;
            case input::Key::D:     return KEY_D;
            case input::Key::SPACE: return KEY_SPACE;
        }

        return KEY_NULL;
    }

    MouseButton toRaylibMouseButton(input::MouseButton mouseButton) {
        switch (mouseButton) {
            case input::MouseButton::LEFT:   return MOUSE_BUTTON_LEFT;
            case input::MouseButton::RIGHT:  return MOUSE_BUTTON_RIGHT;
            case input::MouseButton::MIDDLE: return MOUSE_BUTTON_MIDDLE;
        }

        return static_cast<MouseButton>(-1);
    }
    }

bool input::isDown(Key key) {
    return IsKeyDown(toRaylibKey(key));
}

bool input::wasPressed(Key key) {
    return IsKeyPressed(toRaylibKey(key));
}

bool input::wasReleased(Key key) {
    return IsKeyReleased(toRaylibKey(key));
}

bool input::isDown(MouseButton mouseButton) {
    return IsMouseButtonDown(toRaylibMouseButton(mouseButton));
}

bool input::wasPressed(MouseButton mouseButton) {
    return IsMouseButtonPressed(toRaylibMouseButton(mouseButton));
}

Vector2 input::mouseCameraPosition(Camera2D camera) {
    return GetScreenToWorld2D(mousePosition(), camera);
}

Vector2 input::mousePosition() {
    return GetMousePosition();
}

Vector2 input::mouseDelta() {
    return GetMouseDelta();
}

float input::mouseWheelDelta() {
    return GetMouseWheelMove();
}