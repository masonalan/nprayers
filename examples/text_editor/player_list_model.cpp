//
// Created by James Pickering on 1/1/25.
//

#include "player_list_model.hpp"

#include <trundle/util/unicode.hpp>

namespace examples {

PlayerListModel::PlayerListModel(std::vector<Player>* players) :
    _players{players} {}

auto PlayerListModel::rowCount(Index parent) const -> unsigned int {
    return parent == createIndex()
               ? static_cast<unsigned int>(_players->size())
               : 0;
}

auto PlayerListModel::rowText(Index index) const -> const std::wstring& {
    return _players->at(index.row).name;
}

auto PlayerListModel::rowDecoration(Index index) const -> const std::wstring& {
    return Unicode::Helmet;
}

auto PlayerListModel::index(Index parent, unsigned int row) const -> Index {
    if (parent == createIndex()) {
        return createIndex(row, &_players[row]);
    }
    return createIndex();
}

auto PlayerListModel::hasChildren(Index index) const -> bool {
    return index == createIndex();
}

}
