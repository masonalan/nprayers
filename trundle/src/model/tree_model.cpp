//
// Created by James Pickering on 1/3/25.
//

#include <trundle/model/tree_model.hpp>

namespace trundle {

TreeModel::~TreeModel() = default;

auto TreeModel::setState(Index index, IndexState state) -> void {
    _states[index] = state;
    dataChanged();
}

auto TreeModel::setOnDataChanged(TreeModelCallback&& fn) -> void {
    _onDataChanged = fn;
}

auto TreeModel::dataChanged() -> void {
    if (_onDataChanged) {
        _onDataChanged(this);
    }
}

auto TreeModel::state(Index index) -> IndexState {
    if (!_states.count(index)) {
        _states[index] = IndexState{};
    }
    return _states.at(index);
}

}