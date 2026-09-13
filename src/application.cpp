#include "application.hpp"

bool Application::init() {
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 450;

    InitWindow(windowWidth, windowHeight, "Engine Test Window");
    InitAudioDevice();

    if (!IsWindowReady() || !IsAudioDeviceReady()) {
        return false;
    }

    SetTargetFPS(60);

    return true;
}

void Application::run() {
    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        update(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw();
        EndDrawing();
    }
}

void Application::shutdown() {
    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }

    if (IsWindowReady()) {
        CloseWindow();
    }
}

void Application::update(float dt) {
    player_.update(dt);
}

void Application::draw() {
    player_.draw();
}
