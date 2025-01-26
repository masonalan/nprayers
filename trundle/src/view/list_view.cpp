//
// Created by James Pickering on 12/30/24.
//

#include <trundle/view/list_view.hpp>

#include <trundle/util/enum_math.hpp>
#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/frame_widget.hpp>
#include <trundle/widget/list_widget.hpp>
#include <trundle/widget/widget.hpp>

namespace trundle {

ListView::ListView(Widget* parent) :
    FrameWidget{parent} {
    setFrameStyle(FrameStyle::Window);

    _list = addChild<ListWidget>();
    _list->addLayoutConstraint({LayoutAttr::Left, this, LayoutAttr::Left, 1});
    _list->addLayoutConstraint({LayoutAttr::Right, this, LayoutAttr::Right, -1});
    _list->addLayoutConstraint({LayoutAttr::Top, this, LayoutAttr::Top, 3});
    _list->addLayoutConstraint({LayoutAttr::Bottom, actionBar(), LayoutAttr::Top});
}

auto ListView::setFlags(ListViewFlag flags) -> void {
    clearActions();

    if ((flags & ListViewFlag::Editable) != ListViewFlag::None) {
        addAction(Key::CtrlN, L"Add", [this](auto) {
            if (_addCallback) {
                _addCallback(this, _list->selectedRow() + 1);
            }
            clear();
        });
        addAction(Key::Delete, L"Remove", [this](auto) {
            if (_removeCallback) {
                _removeCallback(this, _list->selectedRow());
            }
            clear();
        });
    }

    actionBar()->displayActions(actions());
}

auto ListView::setOnAdd(ListViewCallback&& fn) -> void {
    _addCallback = fn;
}

auto ListView::setOnRemove(ListViewCallback&& fn) -> void {
    _removeCallback = fn;
}

auto ListView::list() const -> ListWidget* {
    return _list;
}

}