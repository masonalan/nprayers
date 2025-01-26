//
// Created by James Pickering on 12/30/24.
//

#include <trundle/view/text_view.hpp>

#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/frame_widget.hpp>
#include <trundle/widget/text_field_widget.hpp>
#include <trundle/widget/widget.hpp>

namespace trundle {

TextView::TextView(Widget* parent) :
    FrameWidget{parent} {
    setFrameStyle(FrameStyle::Window);

    _field = addChild<TextFieldWidget>();
    _field->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 2},
                                  {LayoutAttr::Right, this, LayoutAttr::Right, -2},
                                  {LayoutAttr::Top, this, LayoutAttr::Top, 3},
                                  {LayoutAttr::Bottom, actionBar(), LayoutAttr::Top, -2}});

    actionBar()->displayActions(_field->actions());
}

auto TextView::textField() const -> TextFieldWidget* {
    return _field;
}

}