//
// Created by James Pickering on 1/25/25.
//

#include "project.hpp"

#include "../api/audio_file.hpp"
#include "../api/pattern.hpp"

namespace examples {

static constexpr auto NumPatterns = 128;

Project::Project() {
    _patterns.reserve(NumPatterns);
    for (auto i = 0; i < NumPatterns; ++i) {
        _patterns.push_back(std::make_unique<Pattern>(this, i));
    }
}

Project::~Project() = default;

auto Project::setName(std::wstring name) -> void {
    _name = std::move(name);
}

auto Project::setCurrentPattern(int idx) -> void {
    if (idx < 0 || idx >= NumPatterns) {
        throw std::runtime_error("Invalid pattern index " + std::to_string(idx));
    }
    _currentPattern = idx;
}

auto Project::setOnPlayheadMoved(ProjectCallback&& fn) -> void {
    _onPlayheadMoved = fn;
}

auto Project::addAudioFile(std::unique_ptr<AudioFile> audioFile) -> void {
    _audioFiles.push_back(std::move(audioFile));
}

auto Project::removeAudioFile(int idx) -> void {
    _audioFiles.erase(_audioFiles.begin() + idx);
}

auto Project::play() -> void {
    if (playing()) {
        return;
    }

    _playing = true;
    _playhead = 0;
    _playStart = std::chrono::high_resolution_clock::now();

    for (const auto& file : audioFiles()) {
        SDL_ResumeAudioStreamDevice(file->stream);
    }
}

auto Project::pause() -> void {
    if (!playing()) {
        return;
    }

    _playing = false;

    for (const auto& file : audioFiles()) {
        SDL_PauseAudioStreamDevice(file->stream);
    }
}

auto Project::tick() -> void {
    if (playing()) {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - _playStart).count();
        const auto ph = (ms / 200) % currentPattern()->steps();
        if (ph != _playhead) {
            _playhead = ph;

            if (_onPlayheadMoved) {
                _onPlayheadMoved(this);
            }

            for (const auto& file : audioFiles()) {
                if (currentPattern()->containsAudioFile(file.get()) && currentPattern()->track(file.get()).at(ph)) {
                    SDL_ClearAudioStream(file->stream);
                    SDL_PutAudioStreamData(file->stream, file->wavData, file->wavDataLen);
                }
            }
        }
    }
}

auto Project::audioFiles() const -> const std::vector<std::unique_ptr<AudioFile>>& {
    return _audioFiles;
}

auto Project::audioFile(int idx) const -> AudioFile* {
    if (idx < 0 || idx >= NumPatterns) {
        throw std::runtime_error("Invalid pattern index " + std::to_string(idx));
    }
    return _audioFiles.at(idx).get();
}

auto Project::name() const -> const std::wstring& {
    return _name;
}

auto Project::pattern(int idx) const -> Pattern* {
    if (idx < 0 || idx >= NumPatterns) {
        throw std::runtime_error("Invalid pattern index " + std::to_string(idx));
    }
    return _patterns.at(idx).get();
}

auto Project::currentPattern() const -> Pattern* {
    return _patterns.at(_currentPattern).get();
}

auto Project::playing() const -> bool {
    return _playing;
}

auto Project::playhead() const -> int {
    return _playhead;
}

}