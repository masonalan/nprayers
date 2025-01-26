//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

#include <set>

namespace trundle {

struct ScreenWidget : FrameWidget {
    ScreenWidget();

    auto index(FrameWidget* frame) const -> int;
    auto focus(FrameWidget* parent, int idx) -> void;
    auto unFocus(const FrameWidget* parent, int idx) -> void;

    auto frameWillAppear(FrameWidget* frame) -> void;
    auto frameWillDisappear(FrameWidget* frame) -> void;

private:
    unsigned int _selectWidgetListener;
    bool _focusLocked{false};

    std::unordered_map<FrameType, int> _focusedWidgetIdx{};
    std::unordered_map<const FrameWidget*, std::vector<FrameWidget*>> _visibleFrames{};
};

}
