//
// Created by James Pickering on 1/12/25.
//

#pragma once

#include <trundle/model/item_model.hpp>

#include <string>

namespace trundle {

struct FilterModel : ItemModel {
    [[nodiscard]] auto rowCount(Index parent) const -> unsigned int override;
    [[nodiscard]] auto rowText(Index index) const -> const std::wstring& override;
    [[nodiscard]] auto rowDecoration(Index index) const -> const std::wstring& override;
    [[nodiscard]] auto index(Index parent, unsigned int row) const -> Index override;
    [[nodiscard]] auto hasChildren(Index index) const -> bool override;
    [[nodiscard]] auto state(Index index) const -> IndexState override;
    [[nodiscard]] auto headerText() const -> std::wstring override;
    [[nodiscard]] auto headerVisible() const -> bool override;

    auto loadChildren(Index parent) -> void override;
    auto setState(Index index, IndexState state) -> void override;
    auto update() -> void override;

    [[nodiscard]] auto mapToSource(Index proxyIndex) const -> Index;
    [[nodiscard]] auto mapFromSource(Index proxyIndex) const -> Index;
    [[nodiscard]] auto filtering() const -> bool;

    auto setFilter(const std::wstring& filter) -> void;
    auto setSourceModel(ItemModel* source) -> void;
    auto refreshProxyIndices() -> void;

private:
    std::wstring _filter{};
    std::unordered_map<Index, Index> _proxyToSource{};
    std::unordered_map<Index, Index> _sourceToProxy{};
    std::vector<Index> _filteredIndices{};

    ItemModel* _sourceModel = nullptr;
};

}