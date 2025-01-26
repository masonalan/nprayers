//
// Created by James Pickering on 1/26/25.
//

#pragma once

#include <trundle/renderer/item_render_delegate.hpp>

namespace trundle {

struct ListItemRenderDelegate : ItemRenderDelegate {
    auto render(const Widget* widget, Index index, glm::ivec2 pos, bool selected, void* options) const -> int override;
};

}
