#include "raylib.h"

int main() {
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 450;

    InitWindow(windowWidth, windowHeight, "Engine Test Window");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib CMake Setup Successful!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
