//
// Created by James Pickering on 1/2/25.
//

#pragma once

#include <trundle/model/item_model.hpp>
#include <trundle/widget/widget.hpp>

#include <functional>
#include <vector>

namespace trundle {

struct ScrollBarWidget;
struct TreeWidget;
struct HeaderRenderDelegate;
struct ItemRenderDelegate;

using TreeWidgetCallback = std::function<void(TreeWidget*)>;

struct TreeIndexRenderOptions {
    int row;
    int level;
};

struct TreeWidget final : Widget {
    explicit TreeWidget(Widget* parent = nullptr);

    auto setModel(Model* model) -> void;
    auto setSelectedRow(int row) -> void;
    auto setOnExpand(TreeWidgetCallback&& fn) -> void;
    auto setOnCollapse(TreeWidgetCallback&& fn) -> void;
    auto setOnSelectionChanged(TreeWidgetCallback&& fn) -> void;
    auto setHeaderRenderDelegate(HeaderRenderDelegate* delegate) -> void;
    auto setItemRenderDelegate(ItemRenderDelegate* delegate) -> void;

    [[nodiscard]] auto selectedIndex() const -> Index;
    [[nodiscard]] auto selectedRow() const -> int;
    [[nodiscard]] auto scrollOffset() const -> int;
    [[nodiscard]] auto model() const -> Model*;

protected:
    auto update() -> void override;
    auto render() const -> void override;

private:
    std::vector<std::string> _items{};
    std::vector<Index> _rows{};

    int _selectedRow{};
    int _scrollOffset{};

    ScrollBarWidget* _scrollBar;
    Model* _model{nullptr};
    TreeWidgetCallback _onExpand;
    TreeWidgetCallback _onCollapse;
    TreeWidgetCallback _onSelectionChanged;
    HeaderRenderDelegate* _headerRenderDelegate;
    ItemRenderDelegate* _itemRenderDelegate;
};

}
