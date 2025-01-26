//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include "../widget/track_widget.hpp"

#include <trundle/model/item_model.hpp>

using namespace trundle;

namespace examples {

struct Project;

struct TrackListModel : ItemModel {
    explicit TrackListModel(Project* project);

    [[nodiscard]] auto rowCount(Index parent) const -> unsigned int override;
    [[nodiscard]] auto rowText(Index index) const -> const std::wstring& override;
    [[nodiscard]] auto rowDecoration(Index index) const -> const std::wstring& override;
    [[nodiscard]] auto index(Index parent, unsigned int row) const -> Index override;
    [[nodiscard]] auto hasChildren(Index index) const -> bool override;
    [[nodiscard]] auto headerText() const -> std::wstring override;
    [[nodiscard]] auto headerVisible() const -> bool override;

    [[nodiscard]] auto project() const -> Project*;

private:
    Project* _project;
};

}
