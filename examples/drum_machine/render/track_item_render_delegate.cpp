//
// Created by James Pickering on 1/27/25.
//

#include "track_item_render_delegate.hpp"

#include "../api/audio_file.hpp"
#include "../api/pattern.hpp"
#include "../api/project.hpp"
#include "../model/track_list_model.hpp"

#include <trundle/trundle.hpp>
#include <trundle/widget/list_widget.hpp>

namespace examples {

auto TrackItemRenderDelegate::render(const Widget* widget, Index index, glm::ivec2 pos, bool selected, void* options) const -> int {
    const auto list = dynamic_cast<const ListWidget*>(widget);
    const auto model = dynamic_cast<const TrackListModel*>(list->model());
    const auto audioFile = static_cast<const AudioFile*>(index.data);
    const auto project = model->project();
    const auto pattern = project->currentPattern();

    /**
     * Draw name
     */
    pos.y += index.row * 2 + 1;
    Trundle::setColorPair(Trundle::defaultColorPair());
    Trundle::moveCursor(pos);

    if (index.row == list->selectedRow()) {
        if (list->focused()) {
            Trundle::setColorPair(Trundle::focusHighlightColorPair());
        } else {
            Trundle::setColorPair(Trundle::highlightColorPair());
        }
    }

    Trundle::print(std::to_wstring(index.row + 1) + L".");
    Trundle::setColorPair(Trundle::defaultColorPair());
    Trundle::moveCursor({pos.x + 4, pos.y});
    Trundle::print(audioFile->displayName, 28 - 6);

    /**
     * Draw fields
     */
    auto blockLoc = glm::ivec2{pos.x + 28, pos.y};
    Trundle::moveCursor(blockLoc);

    for (auto i = 0; i < pattern->steps(); ++i) {
        if (glm::ivec2{i, index.row} == pattern->selectedField()) {
            /**
             * Draw selection box
             */
            auto c = glm::ivec2{blockLoc.x - 1, blockLoc.y};
            Trundle::setColorPair(ColorPair::YellowOnDefault);
            Trundle::moveCursor(c);
            Trundle::print(Unicode::LineVert);
            --c.y;
            Trundle::moveCursor(c);
            Trundle::print(Unicode::CornerTopLeft);
            ++c.x;
            Trundle::moveCursor(c);
            if (i != project->playhead()) {
                Trundle::print(Unicode::LineHoriz);
            } else {
                Trundle::setColorPair(ColorPair::Default);
                Trundle::print(Unicode::BlockLightShade);
                Trundle::setColorPair(ColorPair::YellowOnDefault);
            }
            ++c.x;
            Trundle::moveCursor(c);
            Trundle::print(Unicode::CornerTopRight);
            ++c.y;
            Trundle::moveCursor(c);
            Trundle::print(Unicode::LineVert);
            ++c.y;
            Trundle::moveCursor(c);
            Trundle::print(Unicode::CornerBottomRight);
            --c.x;
            Trundle::moveCursor(c);
            if (i != project->playhead()) {
                Trundle::print(Unicode::LineHoriz);
            } else {
                Trundle::setColorPair(ColorPair::Default);
                Trundle::print(Unicode::BlockLightShade);
                Trundle::setColorPair(ColorPair::YellowOnDefault);
            }
            --c.x;
            Trundle::moveCursor(c);
            Trundle::print(Unicode::CornerBottomLeft);
        } else if (i == project->playhead()) {
            /**
             * Draw playhead indicator
             */
            Trundle::setColorPair(ColorPair::Default);
            Trundle::moveCursor({blockLoc.x, blockLoc.y - 1});
            Trundle::print(Unicode::BlockLightShade);
            Trundle::moveCursor({blockLoc.x, blockLoc.y + 1});
            Trundle::print(Unicode::BlockLightShade);
        } else {
            /**
             * Draw regular block
             */
            Trundle::setColorPair(ColorPair::Default);
            Trundle::moveCursor({blockLoc.x, blockLoc.y - 1});
            if (glm::ivec2{i, index.row - 1} != pattern->selectedField()) {
                Trundle::print(String::Space);
            }
            Trundle::moveCursor({blockLoc.x, blockLoc.y + 1});
            Trundle::print(String::Space);
        }
        Trundle::moveCursor(blockLoc);
        Trundle::setColorPair(i / 4 % 2 ? ColorPair::RedOnDefault : ColorPair::BlueOnDefault);
        Trundle::print(pattern->containsAudioFile(audioFile) && pattern->track(audioFile).at(i) ? Unicode::Block : Unicode::BlockMediumShade);
        blockLoc.x += 2;
    }

    return 2;
}

}