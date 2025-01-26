//
// Created by James Pickering on 1/1/25.
//

#pragma once

#include "player.hpp"

#include <trundle/model/item_model.hpp>

#include <vector>

namespace examples {

using namespace trundle;

struct PlayerListModel final : ItemModel {
    explicit PlayerListModel(std::vector<Player>* players);

    [[nodiscard]] auto rowCount(Index parent) const -> unsigned int override;
    [[nodiscard]] auto rowText(Index index) const -> const std::wstring& override;
    [[nodiscard]] auto rowDecoration(Index index) const -> const std::wstring& override;
    [[nodiscard]] auto index(Index parent, unsigned int row) const -> Index override;
    [[nodiscard]] auto hasChildren(Index index) const -> bool override;

private:
    mutable std::vector<Player>* _players;
};

}
