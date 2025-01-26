//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include <trundle/model/index.hpp>
#include <trundle/model/index_state.hpp>

#include <glm/vec2.hpp>

namespace trundle {

struct Widget;

enum class ForEachOperation {
    Break,
    Continue,
};

using ModelCallback = std::function<void(Model*)>;
using ModelIndexCallback = std::function<ForEachOperation(const Model*, Index)>;

struct IndexRenderDelegate {
    virtual ~IndexRenderDelegate() = default;
    virtual auto render(const Widget* widget, Index index, glm::ivec2 pos, bool selected, void* options) const -> void = 0;
    virtual auto renderHeader(const Widget* widget, glm::ivec2 pos) const -> int = 0;
};

struct Model {
    virtual ~Model() = default;

    [[nodiscard]] virtual auto rowCount(Index parent) const -> unsigned int = 0;
    [[nodiscard]] virtual auto index(Index parent, unsigned int row) const -> Index = 0;
    [[nodiscard]] virtual auto hasChildren(Index index) const -> bool = 0;

    [[nodiscard]] virtual auto headerText() const -> std::wstring;
    [[nodiscard]] virtual auto headerVisible() const -> bool;

    virtual auto loadChildren(Index parent) -> void;
    virtual auto update() -> void;

    virtual auto setState(Index index, IndexState state) -> void;

    [[nodiscard]] virtual auto state(Index index) const -> IndexState;

    auto forEachIndex(Index parent, bool includeUnexpanded, ModelIndexCallback&& fn) -> void;
    auto setOnDataChanged(ModelCallback&& fn) -> void;
    auto dataChanged() -> void;
    auto validateIndex(Index index) const -> void;

    [[nodiscard]] auto root() const -> Index;
    [[nodiscard]] auto createIndex(unsigned int row = 0, void* data = nullptr) const -> Index;

protected:
    std::unordered_map<Index, IndexState> _states{};

private:
    ModelCallback _onDataChanged{nullptr};
    bool _dataChanged{false};
};

}