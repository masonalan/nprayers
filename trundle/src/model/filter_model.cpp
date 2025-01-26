//
// Created by James Pickering on 1/12/25.
//

#include <trundle/model/filter_model.hpp>

#define REQUIRE_SOURCE_MODEL \
    if (!_sourceModel)       \
        throw std::runtime_error("Filter model requires a source model");

namespace trundle {

auto FilterModel::rowCount(Index parent) const -> unsigned int {
    REQUIRE_SOURCE_MODEL
    validateIndex(parent);

    if (!filtering()) {
        return _sourceModel->rowCount(mapToSource(parent));
    }

    if (parent == root()) {
        return _filteredIndices.empty() ? 0 : _filteredIndices.size();
    }

    if (state(parent).expanded()) {
        return _sourceModel->rowCount(mapToSource(parent));
    }

    return 0;
}

auto FilterModel::rowText(Index index) const -> const std::wstring& {
    REQUIRE_SOURCE_MODEL
    validateIndex(index);
    return _sourceModel->rowText(mapToSource(index));
}

auto FilterModel::rowDecoration(Index index) const -> const std::wstring& {
    REQUIRE_SOURCE_MODEL
    validateIndex(index);
    return _sourceModel->rowDecoration(mapToSource(index));
}

auto FilterModel::index(Index parent, unsigned int row) const -> Index {
    REQUIRE_SOURCE_MODEL
    validateIndex(parent);

    if (!filtering()) {
        return mapFromSource(_sourceModel->index(parent, row));
    }

    if (parent == createIndex()) {
        return _filteredIndices.at(row);
    }

    return mapFromSource(_sourceModel->index(parent, row));
}

auto FilterModel::hasChildren(Index index) const -> bool {
    REQUIRE_SOURCE_MODEL
    validateIndex(index);
    return _sourceModel->hasChildren(mapToSource(index));
}

auto FilterModel::state(Index index) const -> IndexState {
    REQUIRE_SOURCE_MODEL
    validateIndex(index);

    if (!filtering()) {
        return _sourceModel->state(mapToSource(index));
    }

    return _states.contains(index) ? _states.at(index) : IndexState{};
}

auto FilterModel::headerText() const -> std::wstring {
    REQUIRE_SOURCE_MODEL
    if (!filtering()) {
        return _sourceModel->headerText();
    }

    return L"Search Results: " + _filter;
}

auto FilterModel::headerVisible() const -> bool {
    return filtering();
}

auto FilterModel::loadChildren(Index parent) -> void {
    REQUIRE_SOURCE_MODEL
    validateIndex(parent);
    _sourceModel->loadChildren(mapToSource(parent));
}

auto FilterModel::mapToSource(Index proxyIndex) const -> Index {
    validateIndex(proxyIndex);
    if (!_proxyToSource.contains(proxyIndex)) {
        throw std::runtime_error("A source index was not found for the specified proxy index.");
    }
    return _proxyToSource.at(proxyIndex);
}

auto FilterModel::mapFromSource(Index sourceIndex) const -> Index {
    REQUIRE_SOURCE_MODEL
    _sourceModel->validateIndex(sourceIndex);
    if (!_sourceToProxy.contains(sourceIndex)) {
        throw std::runtime_error("A proxy index was not found for the specified source index.");
    }
    return _sourceToProxy.at(sourceIndex);
}

auto FilterModel::setState(Index index, IndexState state) -> void {
    if (!filtering()) {
        _sourceModel->setState(_proxyToSource.at(index), state);
    } else {
        ItemModel::setState(index, state);
    }
}

auto FilterModel::setFilter(const std::wstring& filter) -> void {
    REQUIRE_SOURCE_MODEL
    _filter = filter;
    refreshProxyIndices();
}

auto FilterModel::refreshProxyIndices() -> void {
    REQUIRE_SOURCE_MODEL
    _filteredIndices.clear();

    auto resetMap = [](auto& map, auto key, auto value) {
        map.clear();
        map.insert({key, value});
    };

    auto insertPair = [this](auto proxyIdx, auto srcIdx) {
        _proxyToSource.insert({proxyIdx, srcIdx});
        _sourceToProxy.insert({srcIdx, proxyIdx});
    };

    resetMap(_proxyToSource, root(), _sourceModel->root());
    resetMap(_sourceToProxy, _sourceModel->root(), root());

    if (filtering()) {
        auto proxyRow = 0u;
        _sourceModel->forEachIndex(_sourceModel->root(), true, [this, &proxyRow, &insertPair](const auto, const auto index) {
            const auto& text = _sourceModel->rowText(index);
            if (const auto pos = text.find(_filter); pos != std::wstring::npos) {
                const auto proxyIndex = createIndex(proxyRow, index.data);
                _filteredIndices.push_back(proxyIndex);
                insertPair(proxyIndex, index);

                auto s = state(proxyIndex);
                s.start = pos;
                s.length = _filter.size();
                setState(proxyIndex, s);

                if (s.expanded()) {
                    _sourceModel->forEachIndex(index, true, [this, &insertPair](const auto, const auto idx) {
                        const auto proxyIdx = createIndex(idx.row, idx.data);
                        insertPair(proxyIdx, idx);

                        return ForEachOperation::Continue;
                    });
                }

                proxyRow++;

                return proxyRow >= 50 ? ForEachOperation::Break : ForEachOperation::Continue;
            }

            return ForEachOperation::Continue;
        });
    } else {
        _sourceModel->forEachIndex(_sourceModel->root(), false, [this, &insertPair](const auto, const auto index) {
            const auto proxyIndex = createIndex(index.row, index.data);
            insertPair(proxyIndex, index);
            return ForEachOperation::Continue;
        });
    }

    dataChanged();
}

auto FilterModel::setSourceModel(ItemModel* model) -> void {
    _sourceModel = model;
    _sourceModel->setOnDataChanged([this](auto) {
        refreshProxyIndices();
    });
    refreshProxyIndices();
}

auto FilterModel::update() -> void {
    if (_sourceModel) {
        _sourceModel->update();
    }
    ItemModel::update();
}

auto FilterModel::filtering() const -> bool {
    return !_filter.empty();
}

}
