//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include <chrono>
#include <functional>
#include <vector>

namespace examples {

struct AudioFile;
struct Pattern;
struct Project;

using ProjectCallback = std::function<void(Project*)>;

struct Project {
    Project();
    ~Project();

    auto setName(std::wstring name) -> void;
    auto setCurrentPattern(int idx) -> void;
    auto setOnPlayheadMoved(ProjectCallback&& fn) -> void;
    auto addAudioFile(std::unique_ptr<AudioFile> audioFile) -> void;
    auto removeAudioFile(int idx) -> void;

    auto play() -> void;
    auto pause() -> void;
    auto tick() -> void;

    [[nodiscard]] auto name() const -> const std::wstring&;
    [[nodiscard]] auto audioFiles() const -> const std::vector<std::unique_ptr<AudioFile>>&;
    [[nodiscard]] auto audioFile(int idx) const -> AudioFile*;
    [[nodiscard]] auto pattern(int idx) const -> Pattern*;
    [[nodiscard]] auto currentPattern() const -> Pattern*;
    [[nodiscard]] auto playing() const -> bool;
    [[nodiscard]] auto playhead() const -> int;

private:
    ProjectCallback _onPlayheadMoved{nullptr};

    std::vector<std::unique_ptr<AudioFile>> _audioFiles;
    std::vector<std::unique_ptr<Pattern>> _patterns;
    std::wstring _name;

    int _currentPattern{0};

    int _playhead = {0};
    bool _playing{false};
    std::chrono::time_point<std::chrono::high_resolution_clock> _playStart;
};

}
