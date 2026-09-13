#include "application.hpp"

#include "input/input.hpp"

bool Application::init() {
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 450;

    InitWindow(windowWidth, windowHeight, "Engine Test Window");
    InitAudioDevice();

    if (!IsWindowReady() || !IsAudioDeviceReady()) {
        return false;
    }

    SetTargetFPS(60);

    checkerboard = resources::TextureResource::fromImage(
            GenImageChecked(128, 128, 16, 16, DARKBLUE, RAYWHITE));
    font = resources::FontResource("assets/fonts/PixAntiqua.ttf");
    fxWav = resources::SoundResource("assets/sounds/boing_x.wav");

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
    checkerboard.reset();
    fxWav.reset();
    font.reset();

    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }

    if (IsWindowReady()) {
        CloseWindow();
    }
}

void Application::update(float dt) {
    (void)dt;

    if (input::wasPressed(input::Key::SPACE) && fxWav.has_value()) {
        PlaySound(fxWav->get());
    }
}

void Application::draw() {
        if (checkerboard.has_value()) {
            DrawText("TextureResource RAII example", 250, 100, 20, DARKGRAY);
            DrawTexture(checkerboard->get(), 336, 161, WHITE);
        }

        if (font.has_value()) {
            DrawText("Loaded through the wrapper", 280, 330, 20, LIGHTGRAY);
            DrawTextEx(font->get(), "Using custom TTF font!", Vector2{ 20, 80 }, (float)font->get().baseSize, 2, MAROON);
        }
}

