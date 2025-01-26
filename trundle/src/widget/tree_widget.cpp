//
// Created by James Pickering on 1/2/25.
//

#include <trundle/widget/tree_widget.hpp>

#include <trundle/model/filter_model.hpp>
#include <trundle/renderer/abstract_header_render_delegate.hpp>
#include <trundle/renderer/tree_item_render_delegate.hpp>
#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/widget/scroll_bar_widget.hpp>

namespace trundle {

static auto defaultItemRenderDelegate = std::make_unique<TreeItemRenderDelegate>();
static auto defaultHeaderRenderDelegate = std::make_unique<AbstractHeaderRenderDelegate>();

TreeWidget::TreeWidget(Widget* parent) :
    Widget{parent} {
    setItemRenderDelegate(defaultItemRenderDelegate.get());
    setHeaderRenderDelegate(defaultHeaderRenderDelegate.get());

    _scrollBar = addChild<ScrollBarWidget>();
    _scrollBar->addLayoutConstraints({{LayoutAttr::Right, this, LayoutAttr::Right},
                                      {LayoutAttr::Top, this, LayoutAttr::Top},
                                      {LayoutAttr::Bottom, this, LayoutAttr::Bottom}});
}

auto TreeWidget::setModel(Model* model) -> void {
    _model = model;
    _model->setOnDataChanged([this](auto) {
        clear();
        _rows.clear();

        if (!_model->rowCount(_model->createIndex())) {
            _scrollBar->setContentHeight(_rows.size());
            return;
        }

        _model->forEachIndex(_model->root(), false, [this](const auto, const auto index) {
            _rows.push_back(index);
            return ForEachOperation::Continue;
        });

        _scrollBar->setContentHeight(_rows.size());
    });
    _model->dataChanged();
}

auto TreeWidget::setSelectedRow(int row) -> void {
    _selectedRow = row;
    clear();
}

auto TreeWidget::setOnExpand(TreeWidgetCallback&& fn) -> void {
    _onExpand = fn;
}

auto TreeWidget::setOnCollapse(TreeWidgetCallback&& fn) -> void {
    _onCollapse = fn;
}

auto TreeWidget::setOnSelectionChanged(TreeWidgetCallback&& fn) -> void {
    _onSelectionChanged = fn;
}

auto TreeWidget::setHeaderRenderDelegate(HeaderRenderDelegate* delegate) -> void {
    _headerRenderDelegate = delegate;
}

auto TreeWidget::setItemRenderDelegate(ItemRenderDelegate* delegate) -> void {
    _itemRenderDelegate = delegate;
}

auto TreeWidget::selectedIndex() const -> Index {
    return _rows[_selectedRow];
}

auto TreeWidget::selectedRow() const -> int {
    return _selectedRow;
}

auto TreeWidget::scrollOffset() const -> int {
    return _scrollOffset;
}

auto TreeWidget::model() const -> Model* {
    return _model;
}

auto TreeWidget::update() -> void {
    if (focused()) {
        switch (Keyboard::currKey()) {
        case Key::Up: {
            if (const auto row = std::max(_selectedRow - 1, 0); row != _selectedRow) {
                _selectedRow = row;
                if (_onSelectionChanged) {
                    _onSelectionChanged(this);
                }
                if (_selectedRow < _scrollOffset) {
                    --_scrollOffset;
                    _scrollBar->setScrollOffset(_scrollOffset);
                    clear();
                }
            }
            break;
        }
        case Key::Down: {
            if (const auto row = std::min(_selectedRow + 1, static_cast<int>(_rows.size()) - 1); row != _selectedRow) {
                _selectedRow = row;
                if (_onSelectionChanged) {
                    _onSelectionChanged(this);
                }
                if (_selectedRow >= size().y + _scrollOffset - (_model->headerVisible() ? 1 : 0)) {
                    ++_scrollOffset;
                    _scrollBar->setScrollOffset(_scrollOffset);
                    clear();
                }
            }
            break;
        }
        case Key::Enter: {
            auto state = _model->state(_rows[_selectedRow]);
            state.setExpanded(!state.expanded());
            _model->setState(_rows[_selectedRow], state);
            clear();
            if (state.expanded()) {
                _model->loadChildren(_rows[_selectedRow]);
            } else {
                if (_onCollapse) {
                    _onCollapse(this);
                }
            }
            break;
        }
        default:
            break;
        }
    }

    _model->update();
}

auto TreeWidget::render() const -> void {
    if (!_model) {
        return;
    }

    auto row = 0;
    auto level = 0;
    auto offset = 0;

    auto parents = std::vector<Index>{_model->createIndex()};

    if (!_model->headerText().empty()) {
        offset += _headerRenderDelegate->render(this, {pos().x + 1, pos().y});
    }

    auto i = 0;
    for (const auto& index : _rows) {
        const auto state = _model->state(index);
        const auto selected = row == _selectedRow - _scrollOffset;

        if (i >= _scrollOffset && i < _scrollOffset + size().y - offset) {
            const auto p = glm::ivec2{pos().x + level * 2, pos().y + row + offset};
            Trundle::moveCursor(p);
            auto options = TreeIndexRenderOptions{row, level};
            _itemRenderDelegate->render(this, index, p, i == _selectedRow, &options);
            ++row;
        }

        if (state.expanded() && _model->rowCount(index)) {
            ++level;
            // TODO: add parent to stack
            parents.push_back(index);
        } else {
            auto idx = index;
            while (!parents.empty() && _model->rowCount(parents.back()) == idx.row + 1) {
                --level;
                idx = parents.back();
                parents.pop_back();
            }
        }

        ++i;
    }
}

}