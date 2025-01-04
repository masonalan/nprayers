//
// Created by James Pickering on 1/2/25.
//

#include <trundle/widget/tree_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/widget/scroll_bar_widget.hpp>

namespace trundle {

TreeWidget::TreeWidget(Widget* parent) :
    Widget{parent} {
    _scrollBar = addChild<ScrollBarWidget>();
    _scrollBar->addLayoutConstraints({{LayoutAttribute::Right, this, LayoutAttribute::Right},
                                      {LayoutAttribute::Top, this, LayoutAttribute::Top},
                                      {LayoutAttribute::Bottom, this, LayoutAttribute::Bottom}});
}

auto TreeWidget::setModel(TreeModel* model) -> void {
    _model = model;
    _model->setOnDataChanged([this](auto) {
        _rows.clear();

        auto stack = std::vector<Index>{};
        auto index = _model->index(Index{}, 0);

        while (true) {
            const auto rowCount = _model->rowCount(index);
            const auto state = _model->state(index);

            _rows.push_back(index);

            if (state.expanded && rowCount) {
                stack.push_back(index);
                index = _model->index(index, 0);
            } else {
                while (!stack.empty() && _model->rowCount(stack.back()) == index.row + 1) {
                    index = stack.back();
                    stack.erase(stack.end() - 1);
                }

                if (stack.empty()) {
                    break;
                }

                index = _model->index(stack.back(), index.row + 1);
            }
        }

        _scrollBar->setContentHeight(_rows.size());
    });
    _model->dataChanged();
}

auto TreeWidget::setOnExpand(TreeWidgetCallback&& fn) -> void {
    _onExpand = fn;
}

auto TreeWidget::setOnCollapse(TreeWidgetCallback&& fn) -> void {
    _onCollapse = fn;
}

auto TreeWidget::selectedIndex() const -> Index {
    return _rows[_selectedRow];
}

auto TreeWidget::update() -> void {
    if (focused()) {
        switch (Keyboard::currKey()) {
        case Key::Up: {
            if (const auto row = std::max(_selectedRow - 1, 0); row != _selectedRow) {
                _selectedRow = row;
                if (_selectedRow < 0 + _scrollOffset) {
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
                if (_selectedRow >= size().y + _scrollOffset) {
                    ++_scrollOffset;
                    _scrollBar->setScrollOffset(_scrollOffset);
                    clear();
                }
            }
            break;
        }
        case Key::Enter: {
            auto state = _model->state(_rows[_selectedRow]);
            state.expanded = !state.expanded;
            _model->setState(_rows[_selectedRow], state);
            clear();
            if (state.expanded) {
                if (_onExpand) {
                    _onExpand(this);
                }
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
}

auto TreeWidget::render() const noexcept -> void {
    if (!_model) {
        return;
    }

    auto row = 0;
    auto level = 0;
    //auto parent = Index{};

    auto parents = std::vector<Index>{Index{}};

    auto i = 0;
    for (const auto& index : _rows) {
        const auto state = _model->state(index);

        if (i >= _scrollOffset && i < _scrollOffset + size().y) {
            Trundle::moveCursor({pos().x + level * 2, pos().y + row});
            Trundle::print(_model->hasChildren(index) ? (state.expanded ? Unicode::FolderOpened : Unicode::FolderClosed) : String::Space);
            Trundle::print(String::Space);

            if (row == _selectedRow - _scrollOffset) {
                Trundle::setColorPair(Trundle::highlightColorPair());
            }
            Trundle::print(_model->rowText(index), size().x - (level * 2 + 2) - 2);
            if (row == _selectedRow - _scrollOffset) {
                Trundle::setColorPair(Trundle::defaultColorPair());
            }
            ++row;
        }

        if (state.expanded && _model->rowCount(index)) {
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