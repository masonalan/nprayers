//
// Created by James Pickering on 1/23/25.
//

#pragma once

#include <trundle/util/unicode.hpp>
#include <trundle/widget/frame_widget.hpp>

namespace trundle {

enum class MeterType {
    Colored,
    LeftRight
};

struct MeterWidget : FrameWidget {
    explicit MeterWidget(Widget* parent = nullptr);

    auto setValue(double value) -> void;
    auto setMaxValue(double value) -> void;
    auto setMinValue(double value) -> void;
    auto setWidth(int width) -> void;
    auto setMeterType(MeterType type) -> void;
    auto setLeftBound(std::wstring str) -> void;
    auto setRightBound(std::wstring str) -> void;
    auto setUseColors(bool useColors) -> void;

protected:
    auto update() -> void override;
    auto render() const -> void override;

private:
    auto updateValueStr() -> void;

    double _percentage{0.5};
    double _value{0.5};
    double _maxValue{1};
    double _minValue{0};
    int _width{10};
    std::wstring _valueStr{};
    MeterType _type{MeterType::Colored};
    std::wstring _leftBound{Unicode::LineVert};
    std::wstring _rightBound{Unicode::LineVert};
    bool _useColors{true};
};

}
