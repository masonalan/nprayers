//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/widget/widget.hpp>

#include <functional>
#include <string>

namespace trundle {

enum class FrameStyle {
    SingleLine,
    DoubleLine,
    Window,
    Header
};

enum class FrameType {
    Screen,
    Window,
    BottomSheet,
    Dialog,
    Widget,
    Invalid
};

struct ActionBarWidget;
struct FrameWidget;

using FrameWidgetCallback = std::function<void(FrameWidget*)>;

struct FrameWidget : Widget {
    explicit FrameWidget(Widget* parent = nullptr);

    auto setTitle(const std::wstring& title) -> void;
    auto setFrameType(FrameType type) -> void;
    auto setFrameStyle(FrameStyle style) -> void;

    auto setOnHide(FrameWidgetCallback&& fn) -> void;

    [[nodiscard]] auto title() const -> const std::wstring&;
    [[nodiscard]] auto frameStyle() const -> FrameStyle;
    [[nodiscard]] auto frameType() const -> FrameType;
    [[nodiscard]] auto headerHeight() const -> int;
    [[nodiscard]] auto actionBar() const -> ActionBarWidget*;

protected:
    auto render() const -> void override;
    auto update() -> void override;
    auto willAppear() -> void override;
    auto willDisappear() -> void override;

private:
    ActionBarWidget* _actionBar;
    FrameStyle _frameStyle = FrameStyle::SingleLine;
    FrameType _frameType = FrameType::Window;
    FrameWidgetCallback _onHide = nullptr;

    std::wstring _title{};

    unsigned int _headerHeight = 1;
};

}
