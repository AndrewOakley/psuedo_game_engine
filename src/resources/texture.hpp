#pragma once

#include "raylib.h"

namespace resources {
// Owns one Raylib texture. A texture has a single owner, but that ownership
// can be transferred with a move.
class TextureResource {
public:
    explicit TextureResource(const char* filePath);
    ~TextureResource();

    // Takes ownership of a generated Image, uploads it to the GPU, and then
    // releases the temporary CPU-side image.
    [[nodiscard]] static TextureResource fromImage(Image image);

    TextureResource(const TextureResource&) = delete;
    TextureResource& operator=(const TextureResource&) = delete;

    TextureResource(TextureResource&& other) noexcept;
    TextureResource& operator=(TextureResource&& other) noexcept;

    [[nodiscard]] const Texture2D& get() const noexcept;
    [[nodiscard]] bool isValid() const noexcept;

private:
    explicit TextureResource(Texture2D texture) noexcept;

    void reset() noexcept;

    Texture2D texture_{};
};
}