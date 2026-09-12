#include "resources/texture.hpp"

#include <stdexcept>
#include <string>

namespace resources {
    TextureResource::TextureResource(const char* filePath) : texture_(LoadTexture(filePath)) {
        if (!IsTextureValid(texture_)) {
            throw std::runtime_error("Could not load texture: " + std::string(filePath));
        }
    }

    TextureResource::~TextureResource() {
        reset();
    }

    TextureResource TextureResource::fromImage(Image image) {
        Texture2D texture = LoadTextureFromImage(image);
        UnloadImage(image);

        if (!IsTextureValid(texture)) {
            throw std::runtime_error("Could not create texture from image");
        }

        return TextureResource(texture);
    }

    TextureResource::TextureResource(TextureResource&& other) noexcept
        : texture_(other.texture_) {
        other.texture_ = {};
    }

    TextureResource& TextureResource::operator=(TextureResource&& other) noexcept {
        if (this != &other) {
            reset();
            texture_ = other.texture_;
            other.texture_ = {};
        }

        return *this;
    }

    const Texture2D& TextureResource::get() const noexcept {
        return texture_;
    }

    bool TextureResource::isValid() const noexcept {
        return IsTextureValid(texture_);
    }

    TextureResource::TextureResource(Texture2D texture) noexcept
        : texture_(texture) {
    }

    void TextureResource::reset() noexcept {
        if (IsTextureValid(texture_)) {
            UnloadTexture(texture_);
            texture_ = {};
        }
    }
}