//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/util/layout_attribute.hpp>

#include <functional>

namespace trundle {

struct Widget;

using ConstantValueCallback = std::function<double(Widget*)>;
using ConstantValueWidgetCallback = std::function<double(Widget*, Widget*, double)>;

struct LayoutConstraint {
    LayoutConstraint(LayoutAttr yAttr,
                     Widget* xAttr,
                     LayoutAttr xAtr,
                     double constant = 0.0,
                     double multiplier = 1.0);

    LayoutConstraint(LayoutAttr yAttr,
                     Widget* xAttr,
                     LayoutAttr xAtr,
                     ConstantValueWidgetCallback fn,
                     double multiplier = 1.0);

    LayoutConstraint(LayoutAttr yAttr,
                     double constant);

    LayoutConstraint(LayoutAttr yAttr,
                     ConstantValueCallback constantFn);

    Widget* xWidget{};
    LayoutAttr xAttr;
    LayoutAttr yAttr;
    double multiplier{};
    double constant{};
    ConstantValueCallback constantFn;
    ConstantValueWidgetCallback constantFnAttr;
};

}