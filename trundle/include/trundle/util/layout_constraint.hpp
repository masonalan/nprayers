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
    LayoutConstraint(LayoutAttribute yAttr,
                     Widget* xAttr,
                     LayoutAttribute xAtr,
                     double constant = 0.0,
                     double multiplier = 1.0);

    LayoutConstraint(LayoutAttribute yAttr,
                     Widget* xAttr,
                     LayoutAttribute xAtr,
                     ConstantValueWidgetCallback fn,
                     double multiplier = 1.0);

    LayoutConstraint(LayoutAttribute yAttr,
                     double constant);

    LayoutConstraint(LayoutAttribute yAttr,
                     ConstantValueCallback constantFn);

    Widget* xWidget{};
    LayoutAttribute xAttr;
    LayoutAttribute yAttr;
    double multiplier{};
    double constant{};
    ConstantValueCallback constantFn;
    ConstantValueWidgetCallback constantFnAttr;
};

}