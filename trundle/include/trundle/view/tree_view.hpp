//
// Created by James Pickering on 1/4/25.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

namespace trundle {

struct ActionBarWidget;
struct DividerWidget;
struct LabelWidget;
struct TextFieldWidget;
struct TreeWidget;
struct SearchView;

struct TreeView : FrameWidget {
    explicit TreeView(Widget* parent = nullptr);

    [[nodiscard]] auto tree() const -> TreeWidget*;

private:
    auto setSearchFieldVisible(bool visible) -> void;
    
    TreeWidget* _tree;
    SearchView* _searchView;

    bool _searchFieldVisible = false;
};

}