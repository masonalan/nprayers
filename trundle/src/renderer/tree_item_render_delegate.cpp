//
// Created by James Pickering on 1/26/25.
//

#include <trundle/renderer/tree_item_render_delegate.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/widget/tree_widget.hpp>

namespace trundle {

auto TreeItemRenderDelegate::render(const Widget* widget, Index index, glm::ivec2 pos, bool selected, void* options) const -> int {
    const auto tree = dynamic_cast<const TreeWidget*>(widget);
    const auto itemModel = dynamic_cast<ItemModel*>(tree->model());
    const auto opt = static_cast<TreeIndexRenderOptions*>(options);
    const auto state = itemModel->state(index);

    if (selected && tree->focused()) {
        Trundle::setColorPair(Trundle::focusColorPair());
    }
    Trundle::print(itemModel->hasChildren(index) ? (state.expanded() ? Unicode::FolderOpened : Unicode::FolderClosed) : (selected ? Unicode::TriangleRight : String::Space));
    Trundle::setColorPair(Trundle::defaultColorPair());

    Trundle::print(String::Space);

    if (opt->row == tree->selectedRow() - tree->scrollOffset()) {
        Trundle::setColorPair(tree->focused() ? Trundle::focusHighlightColorPair() : Trundle::highlightColorPair());
    }
    const auto& text = itemModel->rowText(index);
    for (auto ci = 0; ci < std::min(tree->size().x - (opt->level * 2 + 2) - 2, static_cast<int>(text.length())); ++ci) {
        if (state.start == ci) {
            Trundle::setColorPair(ColorPair::DefaultOnBlue);
        }
        if (state.start + state.length == ci) {
            if (opt->row == tree->selectedRow() - tree->scrollOffset()) {
                Trundle::setColorPair(tree->focused() ? Trundle::focusHighlightColorPair() : Trundle::highlightColorPair());
            } else {
                Trundle::setColorPair(Trundle::defaultColorPair());
            }
        }
        Trundle::print(text.at(ci));
    }
    Trundle::setColorPair(Trundle::defaultColorPair());

    return 1;
}

}