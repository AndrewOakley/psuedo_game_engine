#include "application.hpp"

#include "raylib.h"

namespace {
constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 450;
constexpr int kTargetFramesPerSecond = 60;

constexpr Rectangle kWorldBounds {
    0.0F,
    0.0F,
    static_cast<float>(kWindowWidth),
    static_cast<float>(kWindowHeight)
};

constexpr Vector2 kProjectileSpawnPosition { 30.0F, 100.0F };
constexpr Vector2 kProjectileDirection { 1.0F, 0.0F };
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

    enemies_.emplace_back(Vector2 { 100.0F, 400.0F });
    walls_.emplace_back(Vector2 { 600.0F, 100.0F }, 20.0F, 200.0F);
    walls_.emplace_back(Vector2 { 700.0F, 100.0F }, 20.0F, 200.0F);

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
    projectileTimer_ += dt;
    while (projectileTimer_ >= projectileCooldown_) {
        projectileTimer_ -= projectileCooldown_;
        spawnProjectile();
    }

    player_.update(dt);

    for (entities::Projectile& projectile : projectiles_) {
        projectile.update(dt);
    }

    for (entities::Enemy& enemy : enemies_) {
        enemy.update(dt);
    }

    std::erase_if(projectiles_, [](const entities::Projectile& projectile) {
        return !projectile.isAlive() || !CheckCollisionRecs(projectile.bounds(), kWorldBounds);
    });
}

void Application::draw() {
    for (const entities::Wall& wall : walls_) {
        wall.draw();
    }

    for (const entities::Enemy& enemy : enemies_) {
        enemy.draw();
    }

    for (const entities::Projectile& projectile : projectiles_) {
        projectile.draw();
    }

    player_.draw();
}

void Application::spawnProjectile() {
    projectiles_.emplace_back(kProjectileSpawnPosition, kProjectileDirection);
}
