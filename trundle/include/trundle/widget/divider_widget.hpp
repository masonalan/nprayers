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

struct DividerWidget : public Widget {
    using Widget::Widget;

    auto setDividerOrientation(DividerOrientation orientation) -> void;

protected:
    auto render() const noexcept -> void override;

private:
    DividerOrientation _orientation = DividerOrientation::Vertical;
};

}
