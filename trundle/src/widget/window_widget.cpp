//
// Created by James Pickering on 12/26/24.
//

#include <trundle/widget/window_widget.hpp>

#include <trundle/util/keyboard.hpp>

namespace trundle {

WindowWidget::WindowWidget(trundle::Widget* parent) :
    FrameWidget{parent},
    _selectWidgetListener{
        Keyboard::addListener([this](auto& event) {
            if (Keyboard::currKey() == Key::ShiftTab) {
                children()[_selectedWidget]->setFocused(false);
                ++_selectedWidget;
                if (_selectedWidget == children().size()) {
                    _selectedWidget = 0;
                }
                children()[_selectedWidget]->setFocused(true);
                event.accept();
            }
        })} {
}

auto WindowWidget::childAdded() -> void {
    if (children().size() - 1 == _selectedWidget) {
        children().back()->setFocused(true);
    }
}

}