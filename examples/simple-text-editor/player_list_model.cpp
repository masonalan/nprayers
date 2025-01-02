//
// Created by James Pickering on 1/1/25.
//

#include "player_list_model.hpp"

namespace examples {

PlayerListModel::PlayerListModel(const std::vector<Player>* players) :
    _players{players} {}

auto PlayerListModel::rowCount() const -> unsigned int {
    return static_cast<unsigned int>(_players->size());
}

auto PlayerListModel::rowText(unsigned int row) const -> const std::wstring& {
    return _players->at(row).name;
}

}
