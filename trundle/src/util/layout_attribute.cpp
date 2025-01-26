//
// Created by James Pickering on 12/26/24.
//

#include <trundle/util/layout_attribute.hpp>

namespace trundle {

auto layoutAttributeToString(LayoutAttr attr) -> std::string {
    switch (attr) {
    case LayoutAttr::Left:
        return "Left";
    case LayoutAttr::Right:
        return "Right";
    case LayoutAttr::Top:
        return "Top";
    case LayoutAttr::Bottom:
        return "Bottom";
    case LayoutAttr::Width:
        return "Width";
    case LayoutAttr::Height:
        return "Height";
    default:
        return "Unkown (" + std::to_string(static_cast<std::underlying_type_t<LayoutAttr>>(attr)) + ")";
    }
}

auto layoutAttributeValueNotSetOrImplicit(std::optional<LayoutAttributeValue> value) -> bool {
    return !value.has_value() || value.value().priority == LayoutAttributeValuePriority::Implicit;
}

}