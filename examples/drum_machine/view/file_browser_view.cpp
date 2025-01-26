//
// Created by James Pickering on 1/22/25.
//

#include "file_browser_view.hpp"

#include <trundle/util/key.hpp>
#include <trundle/widget/action_bar_widget.hpp>

namespace examples {

FileBrowserView::FileBrowserView(Widget* parent) :
    TreeView{parent} {
    addAction(Key::ShiftRight, L"Add Sample", [this](auto) {
        if (_onSelectionOpened) {
            _onSelectionOpened();
        }
    });

    actionBar()->displayActions(actions());
}

auto FileBrowserView::setOnSelectionOpened(std::function<void()>&& fn) -> void {
    _onSelectionOpened = fn;
}

}