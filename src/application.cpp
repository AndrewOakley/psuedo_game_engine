#include "application.hpp"

#include <string>

#include "raymath.h"
#include "raylib.h"

#include "input/input.hpp"
#include "resources/font.hpp"

namespace {
constexpr int kWindowWidth = 800;
constexpr int kWindowHeight = 450;
constexpr int kTargetFramesPerSecond = 60;
constexpr float kWallThickness = 20.0F;
constexpr float kEnemySpawnMargin = 50.0F;

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

    enemies_.emplace_back(Vector2 { 100.0f, 300.0f });

    walls_.emplace_back(Vector2 { 0.0F, 0.0F }, kWindowWidth, kWallThickness);
    walls_.emplace_back(Vector2 { 0.0F, kWindowHeight - kWallThickness }, kWindowWidth, kWallThickness);
    walls_.emplace_back(Vector2 { 0.0F, 0.0F }, kWallThickness, kWindowHeight);
    walls_.emplace_back(Vector2 { kWindowWidth - kWallThickness, 0.0F }, kWallThickness, kWindowHeight);

    camera.target = { player_.position().x, player_.position().y };
    camera.offset = { kWindowWidth / 2.0f, kWindowHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    return true;
}

Application::~Application() {
    shutdown();
}

void Application::run() {
    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        if (player_.isAlive() && !hasWon_) {
            update(dt);
        }

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
    camera.target = { player_.position().x, player_.position().y };

    enemySpawnTimer_ += dt;
    while (enemySpawnTimer_ >= enemySpawnCooldown_) {
        enemySpawnTimer_ -= enemySpawnCooldown_;
        spawnEnemy();
    }

    if (input::wasPressed(input::Key::SPACE)) {
        spawnProjectile();
    }

    updateEntities(dt);
    resolveCollisions();
    removeDestroyedEntities();
}

void Application::draw() {
    BeginMode2D(camera);
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
    EndMode2D();

    const std::string healthText = "Health: " + std::to_string(player_.health());
    const std::string progressText = "Enemies: " + std::to_string(enemiesDefeated_) + "/" + std::to_string(kEnemiesToDefeat);
    DrawTextEx(font_->get(), healthText.c_str(), { 30.0F, 30.0F }, 20.0F, 0.0F, RED);
    DrawTextEx(font_->get(), progressText.c_str(), { 30.0F, 55.0F }, 20.0F, 0.0F, BLACK);

    if (!player_.isAlive()) {
        DrawTextEx(font_->get(), "GAME OVER", { 320.0F, 200.0F }, 30.0F, 0.0F, BLACK);
    } else if (hasWon_) {
        DrawTextEx(font_->get(), "ROOM CLEAR", { 300.0F, 200.0F }, 30.0F, 0.0F, DARKGREEN);
    }
}

void Application::updateEntities(float dt) {
    player_.update(dt);

    for (entities::Projectile& projectile : projectiles_) {
        projectile.update(dt);
    }

    for (entities::Enemy& enemy : enemies_) {
        enemy.update(dt, player_.position());
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

    for (entities::Enemy& enemy : enemies_) {
        if (!enemy.isAlive()) {
            continue;
        }

        if (CheckCollisionRecs(player_.bounds(), enemy.bounds())) {
            player_.resolveCollision(enemy.bounds());
            if (enemy.damagesPlayer()) {
                player_.takeDamage();
            }
        } else {
            enemy.resetPlayerDamage();
        }
    }
}

void Application::removeDestroyedEntities() {
    std::erase_if(projectiles_, [](const entities::Projectile& projectile) {
        return !projectile.isAlive() || !CheckCollisionRecs(projectile.bounds(), kWorldBounds);
    });

    const auto defeatedEnemies = std::erase_if(enemies_, [](const entities::Enemy& enemy) {
        return !enemy.isAlive();
    });

    enemiesDefeated_ += static_cast<int>(defeatedEnemies);
    hasWon_ = enemiesDefeated_ >= kEnemiesToDefeat;
}

void Application::spawnProjectile() {
    const Vector2 mouseCameraPosition = input::mouseCameraPosition(camera);
    const Vector2 direction = Vector2Subtract(mouseCameraPosition, player_.position());
    if (Vector2LengthSqr(direction) == 0.0F) {
        return;
    }

    projectiles_.emplace_back(player_.position(), direction);
}

void Application::spawnEnemy() {
    std::uniform_int_distribution<int> sideDistribution(0, 3);
    std::uniform_real_distribution<float> xDistribution(0.0F, static_cast<float>(kWindowWidth));
    std::uniform_real_distribution<float> yDistribution(0.0F, static_cast<float>(kWindowHeight));

    Vector2 spawnPosition {};
    switch (sideDistribution(randomEngine_)) {
    case 0:
        spawnPosition = { xDistribution(randomEngine_), -kEnemySpawnMargin };
        break;
    case 1:
        spawnPosition = { xDistribution(randomEngine_), kWindowHeight + kEnemySpawnMargin };
        break;
    case 2:
        spawnPosition = { -kEnemySpawnMargin, yDistribution(randomEngine_) };
        break;
    default:
        spawnPosition = { kWindowWidth + kEnemySpawnMargin, yDistribution(randomEngine_) };
        break;
    }

    enemies_.emplace_back(spawnPosition);
}
