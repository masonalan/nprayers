//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include <unordered_map>
#include <vector>

#include <glm/vec2.hpp>

namespace examples {

struct AudioFile;
struct Project;

struct Pattern {
    Pattern(Project* project, int idx);
    ~Pattern();

    auto addAudioFile(AudioFile* file) -> void;
    auto setSteps(int steps) -> void;
    auto setName(std::wstring name) -> void;
    auto setSelectedField(glm::ivec2 field) -> void;

    [[nodiscard]] auto containsAudioFile(const AudioFile* file) const -> bool;
    [[nodiscard]] auto track(const AudioFile* file) -> std::vector<bool>&;
    [[nodiscard]] auto steps() const -> int;
    [[nodiscard]] auto name() const -> const std::wstring&;
    [[nodiscard]] auto selectedField() const -> glm::ivec2;

private:
    int _idx;
    int _steps;
    std::unordered_map<const AudioFile*, std::vector<bool>> _tracks;
    std::wstring _name{L"Pattern 1"};
    glm::ivec2 _selectedField;
    Project* _project;
};

}