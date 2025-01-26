//
// Created by James Pickering on 1/27/25.
//

#pragma once

#include <trundle/renderer/header_render_delegate.hpp>

namespace trundle {
struct Widget;
}

using namespace trundle;

namespace examples {

class TrackHeaderRenderDelegate : public HeaderRenderDelegate {
    auto render(const Widget* widget, glm::ivec2 pos) const -> int override;
};

}
