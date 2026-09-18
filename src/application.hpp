#pragma once

#include <vector>

#include "entities/enemy.hpp"
#include "entities/player.hpp"
#include "entities/projectile.hpp"
#include "entities/wall.hpp"

class Application {
public:
    Application() = default;

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    [[nodiscard]] bool init();

    void run();
    void shutdown();

private:
    entities::Player player_;
    std::vector<entities::Enemy> enemies_;
    std::vector<entities::Wall> walls_;
    std::vector<entities::Projectile> projectiles_;
    float projectileCooldown_ { 0.5F };
    float projectileTimer_ { 0.0F };

    void update(float dt);
    void draw();
    void spawnProjectile();
    void updateEntities(float dt);
    void resolveCollisions();
    void removeDestroyedEntities();
};
