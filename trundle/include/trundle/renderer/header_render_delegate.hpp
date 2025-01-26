//
// Created by James Pickering on 1/26/25.
//

#pragma once

#include <glm/vec2.hpp>

namespace trundle {

struct Widget;

struct HeaderRenderDelegate {
    virtual ~HeaderRenderDelegate() = default;
    virtual auto render(const Widget* widget, glm::ivec2 pos) const -> int = 0;
};

}
