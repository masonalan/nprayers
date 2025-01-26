//
// Created by James Pickering on 12/26/24.
//

#include "trundle/widget/action_bar_widget.hpp"

#include <trundle/widget/window_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>

#include <vector>

namespace trundle {

ScreenWidget::ScreenWidget() :
    FrameWidget{nullptr},
    _selectWidgetListener{
        Keyboard::addListener([this](auto& event) {
            if (_focusLocked) {
                return;
            }

            switch (Keyboard::currKey()) {
            case Key::ShiftTab: {
                if (!_visibleFrames.count(this)) {
                    break;
                }

                const auto idx = _focusedWidgetIdx[FrameType::Window];
                unFocus(this, idx);
                focus(this, idx + 1);

                break;
            }
            case Key::CtrlT: {
                const auto window = _visibleFrames[this][_focusedWidgetIdx[FrameType::Window]];

                if (!_visibleFrames.count(window)) {
                    break;
                }

                const auto idx = _focusedWidgetIdx[FrameType::BottomSheet];
                if (idx < 0) {
                    unFocus(this, _focusedWidgetIdx[FrameType::Window]);
                } else {
                    unFocus(window, idx);
                }
                focus(window, idx + 1);
            }
            default:
                break;
            }
        })} {
    setFrameType(FrameType::Screen);

    for (auto i = 0; i < static_cast<int>(FrameType::Invalid); ++i) {
        _focusedWidgetIdx[static_cast<FrameType>(i)] = -1;
    }

    const auto size = Trundle::windowSize();
    setFrameStyle(FrameStyle::Header);
    addLayoutConstraint({LayoutAttr::Left, 2});
    addLayoutConstraint({LayoutAttr::Top, 1});
    addLayoutConstraint({LayoutAttr::Width, static_cast<double>(size.x - 4)});
    addLayoutConstraint({LayoutAttr::Height, static_cast<double>(size.y - 2)});
}

auto ScreenWidget::index(FrameWidget* frame) const -> int {
    if (const auto frameParent = dynamic_cast<FrameWidget*>(frame->parent()); _visibleFrames.count(frameParent)) {
        if (const auto itr = std::ranges::find(_visibleFrames.at(frameParent), frame);
            itr != _visibleFrames.at(frameParent).end()) {
            return static_cast<int>(std::distance(_visibleFrames.at(frameParent).begin(), itr));
        }
    }

    return -1;
}

auto ScreenWidget::frameWillAppear(FrameWidget* frame) -> void {
    if (const auto frameParent = dynamic_cast<FrameWidget*>(frame->parent())) {
        // Add frame to visible frames
        if (!_visibleFrames.contains(frameParent)) {
            _visibleFrames[frameParent] = std::vector<FrameWidget*>{};
        }
        _visibleFrames[frameParent].push_back(frame);

        // Handle any specific frame type logic
        switch (frame->frameType()) {
        case FrameType::Window:
            if (_focusedWidgetIdx[FrameType::Window] < 0) {
                focus(frameParent, 0);
            }
            break;
        case FrameType::BottomSheet:
        case FrameType::Dialog:
            unFocus(this, _focusedWidgetIdx[FrameType::Window]);
            focus(frameParent, index(frame));
            _focusLocked = frame->frameType() == FrameType::Dialog;
            break;
        default:
            break;
        }
    }
}

auto ScreenWidget::frameWillDisappear(FrameWidget* frame) -> void {
    if (const auto& frameParent = dynamic_cast<FrameWidget*>(frame->parent())) {
        if (_visibleFrames.count(frameParent)) {
            _visibleFrames[frameParent].erase(std::ranges::remove(_visibleFrames[frameParent], frame).begin());
        }
        if (_visibleFrames[frameParent].empty()) {
            _visibleFrames.erase(frameParent);
        }

        switch (frame->frameType()) {
        case FrameType::Window:
            if (frameParent == this) {
                if (_visibleFrames[this].size() - 1 == _focusedWidgetIdx[FrameType::Window]) {
                    focus(frameParent, _focusedWidgetIdx[FrameType::Window]);
                } else if (_focusedWidgetIdx[FrameType::Window] < 0) {
                    focus(frameParent, 0);
                }
            }
            break;
        case FrameType::BottomSheet:
            unFocus(frameParent, index(frameParent));
            focus(this, index(frameParent));
            break;
        case FrameType::Dialog:
            unFocus(frameParent, index(frameParent));
            focus(this, _focusedWidgetIdx[FrameType::Window]);
            _focusLocked = false;
            break;
        default:
            break;
        }


    }
}

auto ScreenWidget::focus(FrameWidget* parent, int idx) -> void {
    if (idx >= _visibleFrames[parent].size()) {
        if (parent->frameType() == FrameType::Window) {
            idx = -1;
        } else {
            idx = 0;
        }
    }

    if (parent->frameType() == FrameType::Window && idx < 0) {
        parent->actionBar()->setVisible(_visibleFrames.at(parent).empty());
        parent->setFocused(true);
        parent->recalculateLayout();
        _focusedWidgetIdx[FrameType::BottomSheet] = idx;
    } else {
        const auto frame = _visibleFrames[parent][idx];
        frame->actionBar()->setVisible(!_visibleFrames.contains(frame) || _visibleFrames.at(frame).empty());
        frame->setFocused(true);
        frame->recalculateLayout();
        _focusedWidgetIdx[frame->frameType()] = idx;
    }
}

auto ScreenWidget::unFocus(const FrameWidget* parent, const int idx) -> void {
    if (_visibleFrames[parent].size() > idx) {
        _visibleFrames[parent][idx]->actionBar()->setVisible(false);
        _visibleFrames[parent][idx]->setFocused(false);
        _visibleFrames[parent][idx]->recalculateLayout();
    }
}

}