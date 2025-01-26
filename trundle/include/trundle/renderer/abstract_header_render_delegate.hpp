//
// Created by James Pickering on 1/26/25.
//

#pragma once

#include <trundle/renderer/header_render_delegate.hpp>

namespace trundle {

struct AbstractHeaderRenderDelegate : HeaderRenderDelegate {
    auto render(const Widget* widget, glm::ivec2 pos) const -> int override;
};

}
