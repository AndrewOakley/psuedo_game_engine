#pragma once

#include "raylib.h"

namespace resources {
// Owns one Raylib font. A font has a single owner, but that ownership can be
// transferred with a move.
class FontResource {
public:
    explicit FontResource(const char* filePath);
    ~FontResource();

    FontResource(const FontResource&) = delete;
    FontResource& operator=(const FontResource&) = delete;

    FontResource(FontResource&& other) noexcept;
    FontResource& operator=(FontResource&& other) noexcept;

    [[nodiscard]] const Font& get() const noexcept;
    [[nodiscard]] bool isValid() const noexcept;

private:
    void reset() noexcept;

    Font font_{};
};
}