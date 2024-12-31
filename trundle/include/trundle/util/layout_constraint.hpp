//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/util/layout_attribute.hpp>

#include <functional>

namespace trundle {

struct Widget;

struct LayoutConstraint {
    LayoutConstraint(LayoutAttribute yAttr,
                     Widget* xAttr,
                     LayoutAttribute xAtr,
                     double constant = 0.0,
                     double multiplier = 1.0);

    LayoutConstraint(LayoutAttribute yAttr,
                     Widget* xAttr,
                     LayoutAttribute xAtr,
                     std::function<double(double)>,
                     double multiplier = 1.0);

    LayoutConstraint(LayoutAttribute yAttr,
                     double constant);

    LayoutConstraint(LayoutAttribute yAttr,
                     std::function<double()> constantFn);

    Widget* xWidget{};
    LayoutAttribute xAttr;
    LayoutAttribute yAttr;
    double multiplier{};
    double constant{};
    std::function<double()> constantFn;
    std::function<double(double)> constantFnAttr;
};

}