//
// Created by James Pickering on 1/23/25.
//

#include <trundle/widget/slider_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/unicode.hpp>

namespace trundle {

auto SliderWidget::setLocation(double loc) {
    _location = loc;
}

auto SliderWidget::render() const -> void {
    Trundle::moveCursor(pos());
    Trundle::print(std::wstring{L"L"});

    for (auto i = -5; i <= 5; ++i) {
        const auto lowerLimit = i / 5.;
        const auto upperLimit = (i + 1) / 5.;
        if (lowerLimit <= _location && upperLimit > _location) {
            Trundle::setColorPair(ColorPair::YellowOnDefault);
            Trundle::print(Unicode::Dot);
            Trundle::setColorPair(Trundle::defaultColorPair());
        } else {
            Trundle::print(String::Space);
        }
    }

    Trundle::moveCursor({pos().x + 11, pos().y});
    Trundle::print(std::wstring{L"R"});
}

}