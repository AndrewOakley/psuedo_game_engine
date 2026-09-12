#include "resources/sound.hpp"

#include <stdexcept>
#include <string>

namespace resources {
    SoundResource::SoundResource(const char* filePath) : sound_(LoadSound(filePath)) {
        if (!IsSoundValid(sound_)) {
            throw std::runtime_error("Could not load sound: " + std::string(filePath));
        }
    }

    SoundResource::~SoundResource() {
        reset();
    }

    SoundResource::SoundResource(SoundResource&& other) noexcept
        : sound_(other.sound_) {
        other.sound_ = {};
    }

    SoundResource& SoundResource::operator=(SoundResource&& other) noexcept {
        if (this != &other) {
            reset();
            sound_ = other.sound_;
            other.sound_ = {};
        }

        return *this;
    }

    const Sound& SoundResource::get() const noexcept {
        return sound_;
    }

    bool SoundResource::isValid() const noexcept {
        return IsSoundValid(sound_);
    }

    void SoundResource::reset() noexcept {
        if (IsSoundValid(sound_)) {
            UnloadSound(sound_);
            sound_ = {};
        }
    }
}