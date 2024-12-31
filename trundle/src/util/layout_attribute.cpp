//
// Created by James Pickering on 12/26/24.
//

#include <trundle/util/layout_attribute.hpp>

namespace trundle {

auto layoutAttributeToString(LayoutAttribute attr) -> std::string {
    switch (attr) {
    case LayoutAttribute::Left:
        return "Left";
    case LayoutAttribute::Right:
        return "Right";
    case LayoutAttribute::Top:
        return "Top";
    case LayoutAttribute::Bottom:
        return "Bottom";
    case LayoutAttribute::Width:
        return "Width";
    case LayoutAttribute::Height:
        return "Height";
    default:
        return "Unkown (" + std::to_string(static_cast<std::underlying_type_t<LayoutAttribute>>(attr)) + ")";
    }
}

auto layoutAttributeValueNotSetOrImplicit(std::optional<LayoutAttributeValue> value) -> bool {
    return !value.has_value() || value.value().priority == LayoutAttributeValuePriority::Implicit;
}

}