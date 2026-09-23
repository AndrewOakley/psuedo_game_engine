#pragma once

#include <optional>
#include <random>
#include <vector>

#include "resources/font.hpp"
#include "entities/enemy.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"
#include "entities/wall.hpp"

class Application {
public:
    Application() = default;
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    [[nodiscard]] bool init();

    void run();

private:
    void shutdown();
    std::optional<resources::FontResource> font_;
    Camera2D camera { 0 };
    entities::Player player_;
    std::vector<entities::Enemy> enemies_;
    std::vector<entities::Wall> walls_;
    std::vector<entities::Projectile> projectiles_;
    float enemySpawnCooldown_ { 1.0f };
    float enemySpawnTimer_ { 0.0f };
    std::mt19937 randomEngine_ { std::random_device {}() };
    int enemiesDefeated_ { 0 };
    bool hasWon_ { false };

    static constexpr int kEnemiesToDefeat = 10;

    void update(float dt);
    void draw();
    void spawnProjectile();
    void spawnEnemy();
    void updateEntities(float dt);
    void resolveCollisions();
    void removeDestroyedEntities();
};
