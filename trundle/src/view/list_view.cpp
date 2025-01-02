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
    setTitleBarStyle(TitleBarStyle::MultiLine);

    _actionBar = addChild<ActionBarWidget>();

    _list = addChild<ListWidget>();
    _list->addLayoutConstraint({LayoutAttribute::Left, this, LayoutAttribute::Left, 1});
    _list->addLayoutConstraint({LayoutAttribute::Right, this, LayoutAttribute::Right, -1});
    _list->addLayoutConstraint({LayoutAttribute::Top, this, LayoutAttribute::Top, 3});
    _list->addLayoutConstraint({LayoutAttribute::Bottom, _actionBar, LayoutAttribute::Top});
}

auto ListView::setFlags(ListViewFlag flags) -> void {
    clearActions();

    if ((flags & ListViewFlag::Editable) != ListViewFlag::None) {
        addAction(Key::CtrlN, "Add", [this](auto) {
            if (_addCallback) {
                _addCallback(this, _list->selectedRow() + 1);
            }
            clear();
        });
        addAction(Key::Delete, "Remove", [this](auto) {
            if (_removeCallback) {
                _removeCallback(this, _list->selectedRow());
            }
            clear();
        });
    }

    _actionBar->displayActions(actions());
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

auto ListView::actionBar() const -> ActionBarWidget* {
    return _actionBar;
}

}