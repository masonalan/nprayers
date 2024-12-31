//
// Created by James Pickering on 12/23/24.
//

#include <trundle/util/layout_constraint.hpp>
#include <utility>

namespace trundle {

LayoutConstraint::LayoutConstraint(LayoutAttribute yAttr,
                                   Widget* xWidget,
                                   LayoutAttribute xAttr,
                                   double constant,
                                   double multiplier) :
    yAttr{yAttr},
    constant{constant},
    xWidget{xWidget},
    xAttr{xAttr},
    multiplier{multiplier},
    constantFn{nullptr},
    constantFnAttr{nullptr} {
}

LayoutConstraint::LayoutConstraint(LayoutAttribute yAttr,
                                   Widget* xWidget,
                                   LayoutAttribute xAttr,
                                   std::function<double(double)> constantFnAttr,
                                   double multiplier) :
    yAttr{yAttr},
    constantFnAttr{std::move(constantFnAttr)},
    constant{},
    xWidget{xWidget},
    xAttr{xAttr},
    multiplier{multiplier},
    constantFn{nullptr} {
}

LayoutConstraint::LayoutConstraint(LayoutAttribute yAttr,
                                   double constant) :
    yAttr{yAttr},
    constant{constant},
    xWidget{nullptr},
    xAttr{LayoutAttribute::None},
    multiplier{1},
    constantFn{nullptr},
    constantFnAttr{nullptr} {
}

LayoutConstraint::LayoutConstraint(LayoutAttribute yAttr,
                                   std::function<double()> constantFn) :
    yAttr{yAttr},
    constant{},
    xWidget{nullptr},
    xAttr{LayoutAttribute::None},
    multiplier{},
    constantFn{std::move(constantFn)},
    constantFnAttr{nullptr} {}

}
