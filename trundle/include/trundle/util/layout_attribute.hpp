//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <string>
#include <optional>

namespace trundle {

enum class LayoutAttribute {
    Width,
    Height,
    Left,
    Right,
    Top,
    Bottom,
    None
};

auto layoutAttributeToString(LayoutAttribute attr) -> std::string;

enum class LayoutAttributeValuePriority {
    Implicit,
    Explicit
};

struct LayoutAttributeValue {
    int result;
    LayoutAttributeValuePriority priority;
};

// TODO: define
auto layoutAttributeValueNotSetOrImplicit(std::optional<LayoutAttributeValue> value) -> bool;

}
