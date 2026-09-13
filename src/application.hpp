#pragma once

#include "entities/player.hpp"

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

    void update(float dt);
    void draw();
};
