//
// Created by James Pickering on 1/23/25.
//

#include <trundle/widget/meter_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/view/prompt_view.hpp>

#include <format>
#include <string>

namespace trundle {

MeterWidget::MeterWidget(Widget* parent) :
    FrameWidget{parent} {
    setFrameStyle(FrameStyle::Window);
    setFrameType(FrameType::BottomSheet);
    setTitle(L"Volume");
}

auto MeterWidget::update() -> void {
    if (focused()) {
        switch (Keyboard::currKey()) {
        case Key::Left:
            setValue(_value - 1);
            break;
        case Key::Right:
            setValue(_value + 1);
            break;
        case Key::CtrlX:
            Prompt::createWithTextField(window(), title(), L"Enter a value:", std::to_wstring(_value), [this](auto prompt) {
                auto valWStr = prompt->value();
                auto valStr = std::string(valWStr.begin(), valWStr.end());
                setValue(std::atoi(valStr.c_str())); }, [](auto) {});
        default:
            break;
        }
    }
}

auto MeterWidget::render() const -> void {
    Trundle::moveCursor(pos());

    auto i = 0;
    auto loc = 0;
    Trundle::print(_leftBound);
    if (_useColors) {
        Trundle::setColorPair(ColorPair::GreenOnDefault);
    }
    for (; i < _width; ++i) {
        if (_type == MeterType::Colored) {
            if (_percentage > i / static_cast<double>(_width)) {
                if (_useColors) {
                    if (i == 4) {
                        Trundle::setColorPair(ColorPair::YellowOnDefault);
                    } else if (i == 8) {
                        Trundle::setColorPair(ColorPair::RedOnDefault);
                    }
                }
                Trundle::print(Unicode::Square);
                loc = i;
            } else {
                Trundle::print(String::Space);
            }
        } else if (_type == MeterType::LeftRight) {
            if (_percentage >= i / static_cast<double>(_width) && _percentage < (i + 1) / static_cast<double>(_width)) {
                Trundle::print(Unicode::Dot);
                loc = i;
            } else {
                Trundle::print(String::Space);
            }
        }
    }
    Trundle::setColorPair(Trundle::defaultColorPair());
    Trundle::print(_rightBound);

    Trundle::moveCursor({pos().x + loc + 1, pos().y + 1});

    Trundle::print(Unicode::CornerBottomLeft);
    if (focused()) {
        Trundle::print(Unicode::TriangleLeft);
        Trundle::setColorPair(ColorPair::WhiteOnYellow);
    } else {
        Trundle::setColorPair(ColorPair::YellowOnDefault);
    }
    Trundle::print(_valueStr);
    Trundle::setColorPair(Trundle::defaultColorPair());
    if (focused()) {
        Trundle::print(Unicode::TriangleRight);
        Trundle::print(String::Space);
    }
    Trundle::print(String::Space);
}

auto MeterWidget::setValue(double value) -> void {
    _value = value;
    updateValueStr();
}

auto MeterWidget::setMaxValue(double value) -> void {
    _maxValue = value;
    updateValueStr();
}

auto MeterWidget::setMinValue(double value) -> void {
    _minValue = value;
    updateValueStr();
}

auto MeterWidget::setWidth(int width) -> void {
    _width = width;
}

auto MeterWidget::setMeterType(MeterType type) -> void {
    _type = type;
}

auto MeterWidget::setLeftBound(std::wstring str) -> void {
    _leftBound = std::move(str);
}

auto MeterWidget::setRightBound(std::wstring str) -> void {
    _rightBound = std::move(str);
}

auto MeterWidget::setUseColors(bool useColors) -> void {
    _useColors = useColors;
}

auto MeterWidget::updateValueStr() -> void {
    _percentage = (_value - _minValue) / (_maxValue - _minValue);
    const auto str = std::format("{:.2f}", _value);
    _valueStr = std::wstring(str.begin(), str.end());
    clear();
}

}