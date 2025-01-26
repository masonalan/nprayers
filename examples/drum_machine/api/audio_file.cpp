//
// Created by James Pickering on 1/25/25.
//

#include "audio_file.hpp"

namespace examples {

AudioFile::AudioFile(std::filesystem::path path, std::wstring displayName) :
    path(std::move(path)),
    displayName(std::move(displayName)),
    spec{} {
    spec = SDL_AudioSpec{};
    if (!SDL_LoadWAV(this->path.c_str(), &spec, &wavData, &wavDataLen)) {
        throw std::runtime_error("Failed to load wav file: " + this->path.string());
    }
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
}

AudioFile::~AudioFile() = default;

}