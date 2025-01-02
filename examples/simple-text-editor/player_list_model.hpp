//
// Created by James Pickering on 1/1/25.
//

#pragma once

#include "player.hpp"

#include <trundle/model/list_model.hpp>

#include <vector>

namespace examples {

struct PlayerListModel final : trundle::ListModel {
    explicit PlayerListModel(const std::vector<Player>* players);

    [[nodiscard]] auto rowCount() const -> unsigned int override;
    [[nodiscard]] auto rowText(unsigned int row) const -> const std::wstring& override;

private:
    const std::vector<Player>* _players;
};

}
