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
    setTitleBarStyle(TitleBarStyle::MultiLine);

    _actionsBar = addChild<ActionBarWidget>();
    _actionsBar->addLayoutConstraint({LayoutAttribute::Left, this, LayoutAttribute::Left});
    _actionsBar->addLayoutConstraint({LayoutAttribute::Right, this, LayoutAttribute::Right});
    _actionsBar->addLayoutConstraint({LayoutAttribute::Bottom, this, LayoutAttribute::Bottom});
    _actionsBar->addLayoutConstraint({LayoutAttribute::Height, _actionsBar, LayoutAttribute::Width, [this](auto w, auto, auto) {
                                          if (!_actionsBar->visible()) {
                                              return 0.0;
                                          }
                                          const auto cols = static_cast<int>(w->layoutAttributeValue(LayoutAttribute::Width).value().result) / 10;
                                          const auto count = _actionsBar->actionsSize() - 1;
                                          return static_cast<double>(count / cols + 2);
                                      }});

    _field = addChild<TextFieldWidget>();
    _field->addLayoutConstraint({LayoutAttribute::Left, this, LayoutAttribute::Left, 2});
    _field->addLayoutConstraint({LayoutAttribute::Right, this, LayoutAttribute::Right, -2});
    _field->addLayoutConstraint({LayoutAttribute::Top, this, LayoutAttribute::Top, 3});
    _field->addLayoutConstraint({LayoutAttribute::Bottom, _actionsBar, LayoutAttribute::Top});

    _actionsBar->displayActions(_field->actions());
}

auto TextView::textField() const -> TextFieldWidget* {
    return _field;
}

auto TextView::actionBar() const -> ActionBarWidget* {
    return _actionsBar;
}

}