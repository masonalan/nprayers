//
// Created by James Pickering on 12/23/24.
//

#include <trundle/util/layout_constraint.hpp>
#include <utility>

namespace trundle {

LayoutConstraint::LayoutConstraint(LayoutAttr yAttr,
                                   Widget* xWidget,
                                   LayoutAttr xAttr,
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

LayoutConstraint::LayoutConstraint(LayoutAttr yAttr,
                                   Widget* xWidget,
                                   LayoutAttr xAttr,
                                   ConstantValueWidgetCallback constantFnAttr,
                                   double multiplier) :
    yAttr{yAttr},
    constantFnAttr{std::move(constantFnAttr)},
    constant{},
    xWidget{xWidget},
    xAttr{xAttr},
    multiplier{multiplier},
    constantFn{nullptr} {
}

LayoutConstraint::LayoutConstraint(LayoutAttr yAttr,
                                   double constant) :
    yAttr{yAttr},
    constant{constant},
    xWidget{nullptr},
    xAttr{LayoutAttr::None},
    multiplier{1},
    constantFn{nullptr},
    constantFnAttr{nullptr} {
}

LayoutConstraint::LayoutConstraint(LayoutAttr yAttr,
                                   ConstantValueCallback constantFn) :
    yAttr{yAttr},
    constant{},
    xWidget{nullptr},
    xAttr{LayoutAttr::None},
    multiplier{},
    constantFn{std::move(constantFn)},
    constantFnAttr{nullptr} {}

}
