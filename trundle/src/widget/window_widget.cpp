//
// Created by James Pickering on 12/26/24.
//

#include <trundle/widget/window_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>

namespace trundle {

WindowWidget::WindowWidget(trundle::Widget* parent) :
    FrameWidget{parent},
    _selectWidgetListener{
        Keyboard::addListener([this](auto& event) {
            if (!_focusLocked && Keyboard::currKey() == Key::ShiftTab) {
                children()[_selectedWidget]->setFocused(false);
                do {
                    ++_selectedWidget;
                    if (_selectedWidget == children().size()) {
                        _selectedWidget = 0;
                    }
                } while (!children().at(_selectedWidget)->visible());
                children()[_selectedWidget]->setFocused(true);
                event.accept();
            }
        })} {
    const auto size = Trundle::windowSize();
    setTitleBarStyle(TitleBarStyle::SingleLine);
    addLayoutConstraint({LayoutAttribute::Left, 2});
    addLayoutConstraint({LayoutAttribute::Top, 1});
    addLayoutConstraint({LayoutAttribute::Width, static_cast<double>(size.x - 4)});
    addLayoutConstraint({LayoutAttribute::Height, static_cast<double>(size.y - 2)});
}

auto WindowWidget::setFocused(Widget* widget) -> void {
    if (_focusedWidget) {
        _focusedWidget->setFocused(false);
    }
    _focusedWidget = widget;
    if (_focusedWidget) {
        widget->setFocused(true);
    }
}

auto WindowWidget::childAdded() -> void {
    if (children().size() - 1 == _selectedWidget) {
        setFocused(children().back().get());
    }
}

auto WindowWidget::setFocusLocked(bool locked) -> void {
    _focusLocked = locked;
}

}