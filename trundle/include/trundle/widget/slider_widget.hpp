//
// Created by James Pickering on 1/23/25.
//

#pragma once

#include <trundle/widget/widget.hpp>

namespace trundle {

struct SliderWidget : public Widget {
    using Widget::Widget;

    auto setLocation(double loc);

protected:
    auto render() const -> void override;

private:
    double _location{-0.2};
};

}
