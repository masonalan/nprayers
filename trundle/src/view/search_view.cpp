//
// Created by James Pickering on 1/15/25.
//

#include "trundle/util/unicode.hpp"

#include <trundle/view/search_view.hpp>

#include <trundle/widget/label_widget.hpp>
#include <trundle/widget/text_field_widget.hpp>

namespace trundle {

SearchView::SearchView(Widget* parent) :
    FrameWidget{parent} {
    setFrameStyle(FrameStyle::Window);
    setTitle(L"Search");

    _label = addChild<LabelWidget>();
    _label->setText(Unicode::MagnifyingGlass);

    _field = addChild<TextFieldWidget>();

    _label->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 2},
                                        {LayoutAttr::Top, this, LayoutAttr::Top, 3},
                                        {LayoutAttr::Width, 1},
                                        {LayoutAttr::Height, 1}});

    _field->addLayoutConstraints({{LayoutAttr::Left, _label, LayoutAttr::Right, 2},
                                        {LayoutAttr::Right, this, LayoutAttr::Right, -2},
                                        {LayoutAttr::Top, _label, LayoutAttr::Top},
                                        {LayoutAttr::Height, 1}});
}

auto SearchView::field() const -> TextFieldWidget* {
    return _field;
}

}