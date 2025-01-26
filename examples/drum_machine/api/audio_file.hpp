//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include <SDL3/SDL_audio.h>

#include <filesystem>
#include <string>

namespace examples {

struct AudioFile {
    AudioFile(std::filesystem::path path, std::wstring displayName);
    ~AudioFile();

    std::filesystem::path path;
    std::wstring displayName;

    Uint8* wavData = nullptr;
    Uint32 wavDataLen = 0;
    SDL_AudioStream* stream{nullptr};
    SDL_AudioSpec spec;
};

}
