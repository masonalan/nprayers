//
// Created by James Pickering on 12/23/24.
//

#include <trundle/widget/frame_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/unicode.hpp>

namespace trundle {

static auto cornerTopLeftChar(TitleBarStyle style) {
    switch (style) {
    case TitleBarStyle::DoubleLine:
        return Unicode::CornerTopLeftHorizDouble;
    default:
        return Unicode::CornerTopLeft;
    }
}

static auto cornerTopRightChar(TitleBarStyle style) {
    switch (style) {
    case TitleBarStyle::DoubleLine:
        return Unicode::CornerTopRightHorizDouble;
    default:
        return Unicode::CornerTopRight;
    }
}

static auto borderTopChar(TitleBarStyle style) {
    switch (style) {
    case TitleBarStyle::DoubleLine:
        return Unicode::LineHorizDouble;
    default:
        return Unicode::LineHoriz;
    }
}

auto FrameWidget::setTitle(const std::string& title) -> void {
    _title = title;
}

auto FrameWidget::setTitleBarStyle(TitleBarStyle style) -> void {
    _titleBarStyle = style;
}

auto FrameWidget::title() const -> const std::string& {
    return _title;
}

auto FrameWidget::titleBarStyle() const -> TitleBarStyle {
    return _titleBarStyle;
}

auto FrameWidget::render() const noexcept -> void {
    if (titleBarStyle() == TitleBarStyle::None) {
        Trundle::moveCursor(pos());
        Trundle::print(title());
        return;
    }

    if (focused()) {
        Trundle::setColorPair(Trundle::focusColorPair());
    }

    Trundle::moveCursor(pos());
    for (auto j = 0; j < size().x; ++j) {
        if (j == 0) {
            Trundle::print(cornerTopLeftChar(titleBarStyle()));
        } else if (j == size().x - 1) {
            Trundle::print(cornerTopRightChar(titleBarStyle()));
        } else {
            Trundle::print(borderTopChar(titleBarStyle()));
        }
    }

    auto bodyPos = glm::ivec2{pos().x, pos().y + 1};

    if (titleBarStyle() == TitleBarStyle::MultiLine) {
        Trundle::moveCursor({pos().x, pos().y + 1});
        Trundle::print(Unicode::LineVert);
        Trundle::moveCursor({pos().x + size().x - 1, pos().y + 1});
        Trundle::print(Unicode::LineVert);

        Trundle::moveCursor({pos().x, pos().y + 2});
        Trundle::print(Unicode::LineVertRight);
        for (auto x = pos().x + 1; x < pos().x + size().x - 1; ++x) {
            Trundle::print(Unicode::LineHoriz);
        }
        Trundle::print(Unicode::LineVertLeft);

        bodyPos.y += 2;
    }

    for (auto y = bodyPos.y; y < pos().y + size().y - 1; ++y) {
        Trundle::moveCursor({pos().x, y});
        Trundle::print(Unicode::LineVert);
        Trundle::moveCursor({pos().x + size().x - 1, y});
        Trundle::print(Unicode::LineVert);
    }

    Trundle::moveCursor({pos().x, pos().y + size().y - 1});
    for (auto x = 0; x < size().x; ++x) {
        if (x == 0) {
            Trundle::print(Unicode::CornerBottomLeft);
        } else if (x == size().x - 1) {
            Trundle::print(Unicode::CornerBottomRight);
        } else {
            Trundle::print(Unicode::LineHoriz);
        }
    }

    if (focused()) {
        Trundle::setColorPair(Trundle::defaultColorPair());
    }

    if (titleBarStyle() == TitleBarStyle::MultiLine) {
        Trundle::moveCursor({pos().x + 2, pos().y + 1});
    } else {
        Trundle::moveCursor({pos().x + 2, pos().y});
    }
    Trundle::print(title());
}

}