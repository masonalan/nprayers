//
// Created by James Pickering on 1/25/25.
//

#include <trundle/model/model.hpp>

namespace trundle {

auto Model::headerText() const -> std::wstring {
    return {};
}

auto Model::headerVisible() const -> bool {
    return false;
}

auto Model::loadChildren(Index parent) -> void {
}

auto Model::forEachIndex(Index parent, bool includeUnexpanded, ModelIndexCallback&& fn) -> void {
    auto stack = std::vector<std::pair<Index, unsigned int>>{};
    auto row = 0u;

    while (true) {
        const auto rc = rowCount(parent);
        if (rc == row || rc == 0) {
            if (stack.empty()) {
                break;
            }

            const auto& [p, r] = stack.back();
            parent = p;
            row = r;

            stack.pop_back();

            continue;
        }

        const auto idx = index(parent, row);

        if (fn(this, idx) == ForEachOperation::Break) {
            return;
        }

        ++row;

        if (includeUnexpanded) {
            loadChildren(idx);
        }

        if ((includeUnexpanded || state(idx).expanded()) && rowCount(idx) > 0) {
            stack.emplace_back(parent, row);
            parent = idx;
            row = 0;
        }
    }
}

auto Model::setState(Index index, IndexState state) -> void {
    _states[index] = state;
    dataChanged();
}

auto Model::setOnDataChanged(ModelCallback&& fn) -> void {
    _onDataChanged = fn;
}

auto Model::dataChanged() -> void {
    _dataChanged = true;
}

auto Model::update() -> void {
    if (_dataChanged && _onDataChanged) {
        _onDataChanged(this);
        _dataChanged = false;
    }
}

auto Model::root() const -> Index {
    return createIndex();
}

auto Model::createIndex(unsigned int row, void* data) const -> Index {
    return Index{this, row, data};
}

auto Model::state(Index index) const -> IndexState {
    if (!_states.contains(index)) {
        return IndexState{};
    }

    return _states.at(index);
}

auto Model::validateIndex(Index index) const -> void {
    if (index.model != this) {
        throw std::invalid_argument("Model does not match current model");
    }
}

}