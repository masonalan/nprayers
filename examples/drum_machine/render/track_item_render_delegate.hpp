//
// Created by James Pickering on 1/27/25.
//

#pragma once

#include <trundle/model/index.hpp>
#include <trundle/renderer/item_render_delegate.hpp>

namespace trundle {
struct Widget;
}

using namespace trundle;

namespace examples {

struct TrackItemRenderDelegate : ItemRenderDelegate {
    auto render(const Widget* widget, Index index, glm::ivec2 pos, bool selected, void* options) const -> int override;
};

}
