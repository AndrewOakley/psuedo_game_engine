#include "resources/font.hpp"

#include <stdexcept>
#include <string>

namespace resources {
    FontResource::FontResource(const char* filePath)
        : font_(LoadFont(filePath)) {
        if (!IsFontValid(font_)) {
            throw std::runtime_error("Could not load font: " + std::string(filePath));
        }
    }

    FontResource::~FontResource() {
        reset();
    }

    FontResource::FontResource(FontResource&& other) noexcept
        : font_(other.font_) {
        other.font_ = {};
    }

    FontResource& FontResource::operator=(FontResource&& other) noexcept {
        if (this != &other) {
            reset();
            font_ = other.font_;
            other.font_ = {};
        }

        return *this;
    }

    const Font& FontResource::get() const noexcept {
        return font_;
    }

    bool FontResource::isValid() const noexcept {
        return IsFontValid(font_);
    }

    void FontResource::reset() noexcept {
        if (IsFontValid(font_)) {
            UnloadFont(font_);
            font_ = {};
        }
    }
}