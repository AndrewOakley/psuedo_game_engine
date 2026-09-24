#include "application.hpp"

#include <string>

#include "raymath.h"
#include "raylib.h"

#include "input/input.hpp"
#include "resources/font.hpp"

namespace {
constexpr int kWindowWidth = 810;
constexpr int kWindowHeight = 450;
constexpr int kTargetFramesPerSecond = 60;
constexpr float kWallThickness = 30.0F;
constexpr float kEnemySpawnMargin = 50.0F;
const int cellSize = 30;

constexpr Rectangle kWorldBounds {
    0.0f,
    0.0f,
    static_cast<float>(kWindowWidth),
    static_cast<float>(kWindowHeight)
};
}

bool Application::init() {
    InitWindow(kWindowWidth, kWindowHeight, "Engine Test Window");

    if (!IsWindowReady()) {
        return false;
    }

    InitAudioDevice();

    if (!IsAudioDeviceReady()) {
        CloseWindow();
        return false;
    }

    SetTargetFPS(kTargetFramesPerSecond);

    font_ = resources::FontResource("assets/fonts/PixAntiqua.ttf");

    walls_.emplace_back(Vector2 { 0.0F, 0.0F }, kWindowWidth, kWallThickness);
    walls_.emplace_back(Vector2 { 0.0F, kWindowHeight - kWallThickness }, kWindowWidth, kWallThickness);
    walls_.emplace_back(Vector2 { 0.0F, 0.0F }, kWallThickness, kWindowHeight);
    walls_.emplace_back(Vector2 { kWindowWidth - kWallThickness, 0.0F }, kWallThickness, kWindowHeight);

    spawnApple();

    return true;
}

Application::~Application() {
    shutdown();
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
    font_.reset();

    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }

    if (IsWindowReady()) {
        CloseWindow();
    }
}

void Application::update(float dt) {
    updateEntities(dt);
    resolveCollisions();
}

void Application::draw() {
    for (int x = 0; x <= kWindowWidth; x += cellSize) {
        DrawLine(x, 0, x, kWindowHeight, LIGHTGRAY);
    }

    for (int y = 0; y <= kWindowHeight; y += cellSize) {
        DrawLine(0, y, kWindowWidth, y, LIGHTGRAY);
    }

    for (const entities::Wall& wall : walls_) {
        wall.draw();
    }

    snakeChain_.draw();
    apple_.draw();

    if (!snakeChain_.isAlive()) {
        DrawTextEx(font_->get(), "GAME OVER", { 320.0F, 200.0F }, 30.0F, 0.0F, BLACK);
    } else if (hasWon_) {
        DrawTextEx(font_->get(), "ROOM CLEAR", { 300.0F, 200.0F }, 30.0F, 0.0F, DARKGREEN);
    }
}

void Application::updateEntities(float dt) {
    if (!snakeChain_.isAlive()) return;

    snakeChain_.update(dt);
}

void Application::resolveCollisions() {
    if (CheckCollisionRecs(snakeChain_.bounds(), apple_.bounds())) {
        spawnApple();
        snakeChain_.addChain();
    }

    for (const entities::Wall& wall : walls_) {
        if (CheckCollisionRecs(snakeChain_.bounds(), wall.bounds())) {
            snakeChain_.setIsAlive(false);
        }
    }
}

void Application::spawnApple() {
    std::uniform_real_distribution<float> xDistribution(cellSize, static_cast<float>(kWindowWidth - cellSize));
    std::uniform_real_distribution<float> yDistribution(cellSize, static_cast<float>(kWindowHeight - cellSize));

    do {
        float randX = xDistribution(randomEngine_);
        float randY = yDistribution(randomEngine_);
        Vector2 newPosition = { randX - (float)std::fmod(randX, cellSize) + cellSize / 2.0f, randY - (float)std::fmod(randY, cellSize) + cellSize / 2.0f };
        apple_.setPosition(newPosition);
    } while (snakeChain_.anyCollision(apple_.bounds()));
}