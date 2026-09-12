#include "raylib.h"

#include "resources/texture.hpp"
#include "resources/font.hpp"
#include "resources/sound.hpp"

int main() {
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 450;

    InitWindow(windowWidth, windowHeight, "Engine Test Window");
    InitAudioDevice(); 
    SetTargetFPS(60);

    {
        resources::TextureResource checkerboard = resources::TextureResource::fromImage(
            GenImageChecked(128, 128, 16, 16, DARKBLUE, RAYWHITE));
        
        resources::FontResource font("../assets/fonts/PixAntiqua.ttf");
        resources::SoundResource fxWav("../assets/sounds/boing_x.wav");

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            if (IsKeyPressed(KEY_SPACE)) {
                PlaySound(fxWav.get());
            }

            DrawText("TextureResource RAII example", 250, 100, 20, DARKGRAY);
            DrawTexture(checkerboard.get(), 336, 161, WHITE);
            DrawText("Loaded through the wrapper", 280, 330, 20, LIGHTGRAY);

            DrawTextEx(font.get(), "Using custom TTF font!", Vector2{ 20, 80 }, (float)font.get().baseSize, 2, MAROON);

            EndDrawing();
        }
    }

    CloseWindow();
    CloseAudioDevice(); 
    return 0;
}
