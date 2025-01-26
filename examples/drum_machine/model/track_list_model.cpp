//
// Created by James Pickering on 1/25/25.
//

#include "track_list_model.hpp"

#include "../api/audio_file.hpp"
#include "../api/project.hpp"

#include <trundle/util/unicode.hpp>

namespace examples {

TrackListModel::TrackListModel(Project* project) :
    _project{project} {
}

auto TrackListModel::rowCount(Index parent) const -> unsigned int {
    if (parent == root()) {
        return _project->audioFiles().size();
    }
    return 0;
}

auto TrackListModel::rowText(Index index) const -> const std::wstring& {
    return static_cast<AudioFile*>(index.data)->displayName;
}

auto TrackListModel::rowDecoration(Index index) const -> const std::wstring& {
    return String::Space;
}

auto TrackListModel::index(Index parent, unsigned int row) const -> Index {
    return Index{this, row, static_cast<void*>(_project->audioFile(static_cast<int>(row)))};
}

auto TrackListModel::hasChildren(Index parent) const -> bool {
    return parent == root();
}

auto TrackListModel::project() const -> Project* {
    return _project;
}

auto TrackListModel::headerText() const -> std::wstring {
    return L"yayyy";
}

auto TrackListModel::headerVisible() const -> bool {
    return true;
}

}