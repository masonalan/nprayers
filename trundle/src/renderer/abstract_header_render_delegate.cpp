//
// Created by James Pickering on 1/26/25.
//

#include <trundle/renderer/abstract_header_render_delegate.hpp>

#include <trundle/trundle.hpp>
#include <trundle/widget/tree_widget.hpp>

namespace trundle {

auto AbstractHeaderRenderDelegate::render(const Widget* widget, glm::ivec2 pos) const -> int {
    const auto list = dynamic_cast<const TreeWidget*>(widget);
    const auto itemModel = dynamic_cast<ItemModel*>(list->model());

    Trundle::moveCursor(pos);
    Trundle::setColorPair(ColorPair::RedOnYellow);
    Trundle::print(itemModel->headerText());
    Trundle::setColorPair(ColorPair::Default);

    return 1;
}

}