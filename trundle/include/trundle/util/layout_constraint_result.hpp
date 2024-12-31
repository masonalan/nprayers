//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/util/layout_attribute.hpp>

namespace trundle {

struct Widget;

struct LayoutConstraintResult {
    Widget* widget;
    LayoutAttribute attr;
    double result;
};

}
