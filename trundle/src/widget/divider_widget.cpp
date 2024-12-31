//
// Created by James Pickering on 12/26/24.
//

#include <trundle/widget/divider_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/unicode.hpp>

namespace trundle {

auto DividerWidget::setDividerOrientation(DividerOrientation orientation) -> void {
    _orientation = orientation;
}

auto DividerWidget::render() const noexcept -> void {
    if (focused()) {
        Trundle::setColorPair(Trundle::focusColorPair());
    }
    switch (_orientation) {
    case DividerOrientation::Vertical: {
        Trundle::moveCursor(pos());
        Trundle::print(Unicode::LineHorizDown);
        const auto height = size().y;
        for (auto row = 1; row < height - 1; ++row) {
            Trundle::moveCursor({pos().x, pos().y + row});
            Trundle::print(Unicode::LineVert);
        }
        Trundle::moveCursor({pos().x, pos().y + size().y - 1});
        Trundle::print(Unicode::LineHorizUp);
        break;
    }
    case DividerOrientation::Horizontal:
        Trundle::moveCursor({pos().x + 1, pos().y});
        Trundle::print(Unicode::LineVertRight);
        const auto width = size().x;
        for (auto col = 1; col < width - 3; ++col) {
            Trundle::print(Unicode::LineHoriz);
        }
        Trundle::print(Unicode::LineVertLeft);
        break;
    }
    if (focused()) {
        Trundle::setColorPair(Trundle::defaultColorPair());
    }
}

}
