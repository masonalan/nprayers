//
// Created by James Pickering on 1/25/25.
//

#include <trundle/widget/picker_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/unicode.hpp>

namespace trundle {

PickerWidget::PickerWidget(Widget* parent) :
    FrameWidget{parent} {
}

auto PickerWidget::setOptions(const std::vector<std::wstring>& options) -> void {
    _options = options;
}

auto PickerWidget::update() -> void {
    if (focused()) {
    }
}

auto PickerWidget::render() const -> void {
    if (focused()) {
        Trundle::setColorPair(Trundle::focusColorPair());
    } else {
        Trundle::setColorPair(ColorPair::YellowOnDefault);
    }

    Trundle::print(Unicode::TriangleLeft);

    if (focused()) {
        Trundle::setColorPair(Trundle::focusHighlightColorPair());
    }

    if (_currOption >= 0 && _currOption < _options.size()) {
        Trundle::print(_options.at(_currOption));
    } else {
        Trundle::print(std::wstring{L"..."});
    }

    if (focused()) {
        Trundle::setColorPair(Trundle::focusColorPair());
    } else {
        Trundle::setColorPair(ColorPair::YellowOnDefault);
    }

    Trundle::print(Unicode::TriangleRight);
}

}