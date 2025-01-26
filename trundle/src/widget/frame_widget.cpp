//
// Created by James Pickering on 12/23/24.
//

#include <trundle/widget/frame_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/window_widget.hpp>

namespace trundle {

static auto cornerTopLeftChar(FrameStyle style) {
    switch (style) {
    case FrameStyle::DoubleLine:
        return Unicode::CornerTopLeftHorizDouble;
    default:
        return Unicode::CornerTopLeftRounded;
    }
}

static auto cornerTopRightChar(FrameStyle style) {
    switch (style) {
    case FrameStyle::DoubleLine:
        return Unicode::CornerTopRightHorizDouble;
    case FrameStyle::Window:
    case FrameStyle::SingleLine:
        return Unicode::CornerTopRightRounded;
    default:
        throw std::runtime_error("Invalid style");
    }
}

static auto borderTopChar(FrameStyle style) {
    switch (style) {
    case FrameStyle::DoubleLine:
        return Unicode::LineHorizDouble;
    default:
        return Unicode::LineHoriz;
    }
}

FrameWidget::FrameWidget(Widget* parent) :
    Widget{parent} {
    setFocused(false);
    _actionBar = addChild<ActionBarWidget>();
}

auto FrameWidget::setTitle(const std::wstring& title) -> void {
    _title = title;
}

auto FrameWidget::setFrameStyle(FrameStyle style) -> void {
    _frameStyle = style;
    switch (style) {
    case FrameStyle::Window:
        _headerHeight = 3;
        break;
    case FrameStyle::SingleLine:
    case FrameStyle::DoubleLine:
    case FrameStyle::Header:
        _headerHeight = 1;
        break;
    }
}

auto FrameWidget::setFrameType(FrameType type) -> void {
    _frameType = type;
}

auto FrameWidget::setOnHide(FrameWidgetCallback&& fn) -> void {
    _onHide = fn;
}

auto FrameWidget::title() const -> const std::wstring& {
    return _title;
}

auto FrameWidget::frameStyle() const -> FrameStyle {
    return _frameStyle;
}

auto FrameWidget::frameType() const -> FrameType {
    return _frameType;
}

auto FrameWidget::headerHeight() const -> int {
    return static_cast<int>(_headerHeight);
}

auto FrameWidget::actionBar() const -> ActionBarWidget* {
    return _actionBar;
}

auto FrameWidget::update() -> void {
    if (focused()) {
        if (Keyboard::currKey() == Key::Escape && frameType() == FrameType::BottomSheet) {
            setVisible(false);
            if (_onHide) {
                _onHide(this);
            }
        }
    }
}

auto FrameWidget::render() const -> void {
    if (frameType() == FrameType::BottomSheet) {
        clear();
    }
    auto drawBorderTop = [this]() {
        for (auto j = 0; j < size().x; ++j) {
            if (j == 0) {
                Trundle::print(cornerTopLeftChar(frameStyle()));
            } else if (j == size().x - 1) {
                Trundle::print(cornerTopRightChar(frameStyle()));
            } else {
                Trundle::print(borderTopChar(frameStyle()));
            }
        }
    };

    auto drawBorderBottom = [this]() {
        Trundle::moveCursor({pos().x, pos().y + size().y - 1});
        for (auto x = 0; x < size().x; ++x) {
            if (x == 0) {
                Trundle::print(frameType() == FrameType::BottomSheet ? Unicode::LineHorizUp : Unicode::CornerBottomLeft);
            } else if (x == size().x - 1) {
                Trundle::print(frameType() == FrameType::BottomSheet ? Unicode::LineHorizUp : Unicode::CornerBottomRight);
            } else {
                Trundle::print(Unicode::LineHoriz);
            }
        }
    };

    auto drawBorderSides = [this]() {
        for (auto y = pos().y + _headerHeight; y < pos().y + size().y - 1; ++y) {
            Trundle::moveCursor({pos().x, y});
            Trundle::print(Unicode::LineVert);
            Trundle::moveCursor({pos().x + size().x - 1, y});
            Trundle::print(Unicode::LineVert);
        }
    };

    if (focused()) {
        Trundle::setColorPair(Trundle::focusColorPair());
    }

    switch (_frameStyle) {
    case FrameStyle::SingleLine:
    case FrameStyle::DoubleLine:
        Trundle::moveCursor(pos());

        // Draw top border
        drawBorderTop();

        // Draw left & right borders
        drawBorderSides();

        // Draw bottom border
        drawBorderBottom();

        // Draw title
        Trundle::moveCursor({pos().x + 2, pos().y});
        Trundle::setColorPair(Trundle::defaultColorPair());
        Trundle::print(title());

        break;
    case FrameStyle::Window:
        Trundle::moveCursor(pos());

        // Draw top border
        for (auto j = 0; j < size().x; ++j) {
            if (j == 0) {
                Trundle::print(cornerTopLeftChar(frameStyle()));
            } else if (j == size().x - 1) {
                Trundle::print(cornerTopRightChar(frameStyle()));
            } else {
                Trundle::print(borderTopChar(frameStyle()));
            }
        }

        // Draw title left & right borders
        Trundle::moveCursor({pos().x, pos().y + 1});
        Trundle::print(Unicode::LineVert);
        Trundle::moveCursor({pos().x + size().x - 1, pos().y + 1});
        Trundle::print(Unicode::LineVert);

        // Draw title bottom border
        Trundle::moveCursor({pos().x, pos().y + 2});
        Trundle::print(Unicode::LineVertRight);
        for (auto x = pos().x + 2; x < pos().x + size().x; ++x) {
            Trundle::print(Unicode::LineHoriz);
        }
        Trundle::print(Unicode::LineVertLeft);

        // Draw left & right borders
        drawBorderSides();

        // Draw bottom border
        drawBorderBottom();

        // Draw title decal
        Trundle::moveCursor({pos().x + 2, pos().y + 1});
        if (focused()) {
            Trundle::print(Unicode::BlockLightShade);
            Trundle::print(Unicode::BlockMediumShade);
            Trundle::print(String::Space);
        }

        // Draw title
        Trundle::setColorPair(Trundle::defaultColorPair());
        Trundle::print(title());

        Trundle::print(String::Space);
        Trundle::print(String::Space);
        Trundle::print(String::Space);

        Trundle::moveCursor({pos().x + size().x - 3, pos().y + 1});
        if (frameType() == FrameType::BottomSheet) {
            Trundle::print(Unicode::Minimize);
        } else if (frameType() == FrameType::Dialog) {
            Trundle::print(Unicode::Plus);
        }

        break;
    default:
        Trundle::moveCursor(pos());
        Trundle::print(Unicode::Block);
        Trundle::print(Unicode::BlockMediumShade);
        Trundle::print(Unicode::BlockLightShade);
        Trundle::print(String::Space);
        Trundle::print(title());
        Trundle::print(String::Space);

        for (auto i = 5 + title().size(); i < size().x - 4; ++i) {
            Trundle::print(Unicode::LineHoriz);
        }

        Trundle::moveCursor({pos().x + size().x - 3, pos().y});

        Trundle::print(Unicode::BlockLightShade);
        Trundle::print(Unicode::BlockMediumShade);
        Trundle::print(Unicode::Block);
    }
}

auto FrameWidget::willDisappear() -> void {
    Widget::willDisappear();
    window()->frameWillDisappear(this);
}

auto FrameWidget::willAppear() -> void {
    Widget::willAppear();
    window()->frameWillAppear(this);
}

}