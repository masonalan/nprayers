//
// Created by James Pickering on 1/27/25.
//

#include "track_header_render_delegate.hpp"

#include "../api/pattern.hpp"
#include "../api/project.hpp"
#include "../model/track_list_model.hpp"

#include <trundle/trundle.hpp>
#include <trundle/widget/list_widget.hpp>

namespace examples {

auto TrackHeaderRenderDelegate::render(const Widget* widget, glm::ivec2 pos) const -> int {
    const auto list = dynamic_cast<const ListWidget*>(widget);
    const auto model = dynamic_cast<const TrackListModel*>(list->model());
    const auto project = model->project();
    const auto pattern = project->currentPattern();
    const auto playheadPos = glm::ivec2{pos.x + 28, pos.y};

    Trundle::setColorPair(ColorPair::Default);

    Trundle::moveCursor({pos.x - 1, pos.y + 1});
    Trundle::setColorPair(ColorPair::WhiteOnYellow);
    Trundle::print(Unicode::TriangleDown + L" Tracks:");
    Trundle::setColorPair(Trundle::defaultColorPair());

    for (auto i = 0; i < pattern->steps(); ++i) {
        Trundle::moveCursor({playheadPos.x + i * 2, playheadPos.y});
        if (i == project->playhead()) {
            Trundle::setColorPair(ColorPair::YellowOnDefault);
            Trundle::print(Unicode::TriangleDown);
            Trundle::setColorPair(ColorPair::Default);
        } else {
            Trundle::print(String::Space);
        }
    }

    const auto numbersPos = glm::ivec2{playheadPos.x, playheadPos.y + 1};
    Trundle::moveCursor(numbersPos);

    for (auto i = 0; i < pattern->steps(); ++i) {
        Trundle::moveCursor({numbersPos.x + i * 2, numbersPos.y});
        if (i % 4 == 0) {
            if (i == project->playhead()) {
                Trundle::setColorPair(ColorPair::YellowOnDefault);
            }
            Trundle::print(std::to_wstring(i + 1));
            if (i == project->playhead()) {
                Trundle::setColorPair(ColorPair::Default);
            }
        } else {
            if (i == project->playhead()) {
                Trundle::print(Unicode::BlockLightShade);
            } else {
                Trundle::print(String::Space);
            }
        }
    }

    return 2;
}

}