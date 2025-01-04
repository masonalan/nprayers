//
// Created by James Pickering on 1/2/25.
//

#pragma once

#include <trundle/model/tree_model.hpp>
#include <trundle/widget/widget.hpp>

#include <functional>
#include <vector>

namespace trundle {

struct ScrollBarWidget;
struct TreeWidget;

using TreeWidgetCallback = std::function<void(TreeWidget*)>;

struct TreeWidget final : Widget {
    explicit TreeWidget(Widget* parent = nullptr);

    auto setModel(TreeModel* model) -> void;
    auto setOnExpand(TreeWidgetCallback&& fn) -> void;
    auto setOnCollapse(TreeWidgetCallback&& fn) -> void;

    [[nodiscard]] auto selectedIndex() const -> Index;

protected:
    auto update() -> void override;
    auto render() const noexcept -> void override;

private:
    std::vector<std::string> _items{};
    std::vector<Index> _rows{};

    int _selectedRow{};
    int _scrollOffset{};

    ScrollBarWidget* _scrollBar;
    TreeModel* _model{nullptr};
    TreeWidgetCallback _onExpand;
    TreeWidgetCallback _onCollapse;
};

}
