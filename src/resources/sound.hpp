#pragma once

#include "raylib.h"

namespace resources {
// Owns one Raylib sound. A sound has a single owner, but that ownership
// can be transferred with a move.
class SoundResource {
public:
    explicit SoundResource(const char* filePath);
    ~SoundResource();

    SoundResource(const SoundResource&) = delete;
    SoundResource& operator=(const SoundResource&) = delete;

    SoundResource(SoundResource&& other) noexcept;
    SoundResource& operator=(SoundResource&& other) noexcept;

    [[nodiscard]] const Sound& get() const noexcept;
    [[nodiscard]] bool isValid() const noexcept;

private:
    void reset() noexcept;

    Sound sound_{};
};
}