//
// Created by James Pickering on 1/26/25.
//

#pragma once

#include <trundle/model/index.hpp>

#include <glm/vec2.hpp>

namespace trundle {

struct Widget;

struct ItemRenderDelegate {
    virtual ~ItemRenderDelegate() = default;
    virtual auto render(const Widget* widget,
                        Index index,
                        glm::ivec2 pos,
                        bool selected,
                        void* options) const -> int = 0;
};

}
