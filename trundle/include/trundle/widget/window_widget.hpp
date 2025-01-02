//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

namespace trundle {

struct WindowWidget : FrameWidget {
    explicit WindowWidget(Widget* parent = nullptr);

    auto setFocused(Widget* widget) -> void;
    auto setFocusLocked(bool locked) -> void;

protected:
    auto childAdded() -> void override;

private:
    int _selectedWidget{};
    unsigned int _selectWidgetListener;
    bool _focusLocked{false};
    Widget* _focusedWidget{nullptr};
};

}
