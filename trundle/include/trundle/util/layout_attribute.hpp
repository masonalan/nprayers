//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <string>
#include <optional>

namespace trundle {

enum class LayoutAttr {
    Width,
    Height,
    Left,
    Right,
    Top,
    Bottom,
    None
};

auto layoutAttributeToString(LayoutAttr attr) -> std::string;

enum class LayoutAttributeValuePriority {
    Implicit,
    Explicit
};

struct LayoutAttributeValue {
    int result;
    LayoutAttributeValuePriority priority;
    bool relative;
    int xWidgetValue;
};

// TODO: define
auto layoutAttributeValueNotSetOrImplicit(std::optional<LayoutAttributeValue> value) -> bool;

}
