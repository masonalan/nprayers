//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/widget/widget.hpp>

namespace trundle {

enum class DividerOrientation {
    Vertical,
    Horizontal
};

enum class DividerStyle {
    SingleLine,
    MultiLine,
};

struct DividerWidget : public Widget {
    using Widget::Widget;

    auto setDividerOrientation(DividerOrientation orientation) -> void;
    auto setDividerStyle(DividerStyle style) -> void;

protected:
    auto render() const -> void override;

private:
    DividerOrientation _orientation = DividerOrientation::Vertical;
    DividerStyle _style = DividerStyle::SingleLine;
};

}
