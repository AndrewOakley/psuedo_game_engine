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

    enemies_.emplace_back(Vector2 { 100.0F, 300.0F });
    walls_.emplace_back(Vector2 { 600.0F, 100.0F }, 20.0F, 200.0F);
    walls_.emplace_back(Vector2 { 700.0F, 100.0F }, 80.0F, 200.0F);

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

    updateEntities(dt);
    resolveCollisions();
    removeDestroyedEntities();
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

void Application::updateEntities(float dt) {
    player_.update(dt);

    for (entities::Projectile& projectile : projectiles_) {
        projectile.update(dt);
    }

    for (entities::Enemy& enemy : enemies_) {
        enemy.update(dt);
    }
}

void Application::resolveCollisions() {
    for (entities::Projectile& projectile : projectiles_) {
        if (!projectile.isAlive()) {
            continue;
        }

        // Walls take priority: a projectile stops at the first solid object it hits.
        for (const entities::Wall& wall : walls_) {
            if (CheckCollisionRecs(projectile.bounds(), wall.bounds())) {
                projectile.destroy();
                break;
            }
        }

        if (!projectile.isAlive()) {
            continue;
        }

        for (entities::Enemy& enemy : enemies_) {
            if (!enemy.isAlive()) {
                continue;
            }

            if (CheckCollisionRecs(projectile.bounds(), enemy.bounds())) {
                projectile.destroy();
                enemy.destroy();
                break;
            }
        }
    }

    for (const entities::Wall& wall : walls_) {
        if (CheckCollisionRecs(player_.bounds(), wall.bounds())) {
            player_.resolveCollision(wall.bounds());
        }
    }

    for (const entities::Enemy& enemy : enemies_) {
        if (!enemy.isAlive()) {
            continue;
        }

        if (CheckCollisionRecs(player_.bounds(), enemy.bounds())) {
            player_.resolveCollision(enemy.bounds());
        }
    }
}

void Application::removeDestroyedEntities() {
    std::erase_if(projectiles_, [](const entities::Projectile& projectile) {
        return !projectile.isAlive() || !CheckCollisionRecs(projectile.bounds(), kWorldBounds);
    });

    std::erase_if(enemies_, [](const entities::Enemy& enemy) {
        return !enemy.isAlive();
    });
}

void Application::spawnProjectile() {
    projectiles_.emplace_back(kProjectileSpawnPosition, kProjectileDirection);
}
