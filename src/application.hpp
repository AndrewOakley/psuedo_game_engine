#pragma once

#include <optional>
#include <random>
#include <vector>

#include "resources/font.hpp"
#include "entities/wall.hpp"
#include "entities/snake.hpp"
#include "entities/apple.hpp"

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

    entities::SnakeChain snakeChain_;
    entities::Apple apple_;
    std::vector<entities::Wall> walls_;

    std::mt19937 randomEngine_ { std::random_device {}() };
    bool hasWon_ { false };

    void update(float dt);
    void draw();
    void spawnApple();
    void updateEntities(float dt);
    void resolveCollisions();
};
