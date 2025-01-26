//
// Created by James Pickering on 1/26/25.
//

#include <trundle/renderer/list_item_render_delegate.hpp>

#include <trundle/model/item_model.hpp>
#include <trundle/trundle.hpp>
#include <trundle/widget/list_widget.hpp>

namespace trundle {

auto ListItemRenderDelegate::render(const Widget* widget, Index index, glm::ivec2 pos, bool selected, void* options) const -> int {
    const auto list = dynamic_cast<const ListWidget*>(widget);
    const auto itemModel = dynamic_cast<ItemModel*>(list->model());

    Trundle::print(itemModel->rowDecoration(index));
    pos.x += 3;
    Trundle::moveCursor({pos.x, pos.y + index.row});

    if (selected) {
        Trundle::setColorPair(Trundle::focusHighlightColorPair());
    }
    Trundle::print(itemModel->rowText(index));
    if (selected) {
        Trundle::setColorPair(Trundle::defaultColorPair());
    } else {
        Trundle::print(String::Space);
    }
}

}