//
// Created by James Pickering on 1/25/25.
//

#include "pattern.hpp"

#include "../api/project.hpp"

namespace examples {

Pattern::Pattern(Project* project, int idx) :
    _project{project},
    _idx{idx},
    _steps{} {
    setName(L"Pattern " + std::to_wstring(idx));
    setSteps(32);
}

Pattern::~Pattern() = default;

auto Pattern::setSteps(int steps) -> void {
    _steps = steps;
    for (auto&& [_, notes] : _tracks) {
        auto i = notes.size();
        if (i > _steps) {
            notes.erase(notes.begin() + _steps, notes.end());
        } else {
            for (; i < notes.size(); ++i) {
                notes.emplace_back(false);
            }
        }

        if (notes.size() != _steps) {
            throw std::runtime_error("Notes does not have the correct amount of elements");
        }
    }
}

auto Pattern::setName(std::wstring name) -> void {
    _name = std::move(name);
}

auto Pattern::addAudioFile(AudioFile* file) -> void {
    if (!_tracks.contains(file)) {
        _tracks[file] = std::vector<bool>(_steps);
    }
}

auto Pattern::setSelectedField(glm::ivec2 field) -> void {
    _selectedField = {std::max(std::min(steps() - 1, field.x), 0),
                      std::max(std::min(static_cast<int>(_project->audioFiles().size()) - 1, field.y), 0)};
}

auto Pattern::containsAudioFile(const AudioFile* file) const -> bool {
    return _tracks.contains(file);
}

auto Pattern::track(const AudioFile* file) -> std::vector<bool>& {
    return _tracks[file];
}

auto Pattern::steps() const -> int {
    return _steps;
}

auto Pattern::name() const -> const std::wstring& {
    return _name;
}

auto Pattern::selectedField() const -> glm::ivec2 {
    return _selectedField;
}

}