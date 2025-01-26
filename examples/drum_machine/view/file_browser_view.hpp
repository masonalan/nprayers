//
// Created by James Pickering on 1/22/25.
//

#pragma once

#include <trundle/view/tree_view.hpp>

using namespace trundle;

namespace examples {

struct FileBrowserView : TreeView {
    explicit FileBrowserView(Widget* parent = nullptr);

    auto setOnSelectionOpened(std::function<void()>&& fn) -> void;

private:
    std::function<void()> _onSelectionOpened;
};

}
