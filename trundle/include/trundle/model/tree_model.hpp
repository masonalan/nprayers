//
// Created by James Pickering on 1/2/25.
//

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

namespace trundle {

struct Index {
    unsigned int row;
    void* data;
};

inline auto operator==(const Index& lhs, const Index& rhs) -> bool {
    return lhs.row == rhs.row && lhs.data == rhs.data;
}

}

template <>
struct std::hash<trundle::Index> {
    std::size_t operator()(const trundle::Index& s) const noexcept {
        std::size_t h1 = std::hash<unsigned int>{}(s.row);
        std::size_t h2 = std::hash<void*>{}(s.data);
        return h1 ^ (h2 << 1);
    }
};

namespace trundle {

struct IndexState {
    bool expanded{false};
};

struct TreeModel;

using TreeModelCallback = std::function<void(TreeModel*)>;

struct TreeModel {
    virtual ~TreeModel();

    [[nodiscard]] virtual auto rowCount(Index parent) const -> unsigned int = 0;
    [[nodiscard]] virtual auto rowText(Index index) const -> const std::wstring& = 0;
    [[nodiscard]] virtual auto rowDecoration(Index index) const -> const std::wstring& = 0;
    [[nodiscard]] virtual auto index(Index parent, unsigned int row) const -> Index = 0;
    [[nodiscard]] virtual auto hasChildren(Index index) const -> bool = 0;

    auto setState(Index index, IndexState state) -> void;
    auto setOnDataChanged(TreeModelCallback&& fn) -> void;

    auto dataChanged() -> void;

    [[nodiscard]] auto state(Index index) -> IndexState;

private:
    std::unordered_map<Index, IndexState> _states{};
    TreeModelCallback _onDataChanged{nullptr};
};
}
