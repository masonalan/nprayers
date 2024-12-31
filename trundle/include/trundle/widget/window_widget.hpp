//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

namespace trundle {

struct WindowWidget : public FrameWidget {
    explicit WindowWidget(Widget* parent = nullptr);

protected:
    auto childAdded() -> void override;

private:
    int _selectedWidget{};
    unsigned int _selectWidgetListener;
};

}
