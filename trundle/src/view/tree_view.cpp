//
// Created by James Pickering on 1/4/25.
//

#include "trundle/view/search_view.hpp"
#include "trundle/widget/label_widget.hpp"
#include "trundle/widget/window_widget.hpp"

#include <trundle/view/tree_view.hpp>

#include <trundle/model/filter_model.hpp>
#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/text_field_widget.hpp>
#include <trundle/widget/tree_widget.hpp>

namespace trundle {

TreeView::TreeView(Widget* parent) :
    FrameWidget{parent} {
    setFrameStyle(FrameStyle::Window);

    _searchView = addChild<SearchView>();
    _searchView->setFrameType(FrameType::BottomSheet);
    _searchView->field()->setTextChanged([this](auto) {
        const auto& query = _searchView->field()->text();
        dynamic_cast<FilterModel*>(_tree->model())->setFilter(_searchView->field()->text());
        _tree->setSelectedRow(0);
    });
    _searchView->setOnHide([this](auto) {
        setSearchFieldVisible(false);
    });

    _tree = addChild<TreeWidget>();

    _tree->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 2},
                                 {LayoutAttr::Right, this, LayoutAttr::Right, -2},
                                 {LayoutAttr::Top, this, LayoutAttr::Top, 3},
                                 {LayoutAttr::Bottom, _searchView, LayoutAttr::Top, -1}});

    _searchView->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 1},
                                       {LayoutAttr::Right, this, LayoutAttr::Right, -1},
                                       {LayoutAttr::Height, 6},
                                       {LayoutAttr::Bottom, actionBar(), LayoutAttr::Top}});

    addAction(Key::CtrlF, L"Search", [this](auto) {
        setSearchFieldVisible(!_searchFieldVisible);
    });

    actionBar()->displayActions(actions());

    setSearchFieldVisible(false);
}

auto TreeView::tree() const -> TreeWidget* {
    return _tree;
}

auto TreeView::setSearchFieldVisible(bool visible) -> void {
    _searchView->setVisible(visible);
    recalculateLayout();
}

}