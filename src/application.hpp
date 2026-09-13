#pragma once

#include <optional>
#include "raylib.h"

#include "resources/texture.hpp"
#include "resources/font.hpp"
#include "resources/sound.hpp"

class Application {
public:
    Application() = default;

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    [[nodiscard]] bool init();

    void run();
    void shutdown();

private:
    std::optional<resources::TextureResource> checkerboard;
    std::optional<resources::FontResource> font;
    std::optional<resources::SoundResource> fxWav;

    void update(float dt);
    void draw();
};