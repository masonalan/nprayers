//
// Created by James Pickering on 12/26/24.
//
#include <trundle/widget/list_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/action.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/unicode.hpp>

namespace trundle {

ListWidget::ListWidget(trundle::Widget* parent) :
    Widget{parent} {
}

auto ListWidget::addItem(std::string item) -> void {
    _items.push_back(std::move(item));
}

auto ListWidget::selectRow(int row) -> void {
    _selectedRow = row;
}

auto ListWidget::setOnSelectionChanged(SelectionChangedCallback&& fn) -> void {
    _selectionChangedCallback = fn;
}

auto ListWidget::selectedRow() const -> int {
    return _selectedRow;
}

auto ListWidget::rowCount() const -> int {
    return static_cast<int>(_items.size());
}

auto ListWidget::update() -> void {
    if (focused()) {
        switch (Keyboard::currKey()) {
        case Key::Up:
            if (const auto newRow = std::max(_selectedRow - 1, 0); newRow != _selectedRow) {
                const auto oldRow = _selectedRow;
                _selectedRow = newRow;
                if (_selectionChangedCallback) {
                    _selectionChangedCallback(this, oldRow, newRow);
                }
            }
            break;
        case Key::Down:
            if (const auto newRow = std::min(_selectedRow + 1, static_cast<int>(_model->rowCount()) - 1); newRow != _selectedRow) {
                const auto oldRow = _selectedRow;
                _selectedRow = newRow;
                if (_selectionChangedCallback) {
                    _selectionChangedCallback(this, oldRow, newRow);
                }
            }
            break;
        default:
            break;
        }
    }
}

void ListWidget::render() const noexcept {
    if (!_model) {
        return;
    }

    const auto rows = _model->rowCount();
    for (auto i = 0; i < rows; ++i) {
        if (i == size().y) {
            break;
        }
        Trundle::moveCursor({pos().x + 1, pos().y + i});
        if (i == _selectedRow) {
            Trundle::print(Unicode::ArrowRightDouble);
            Trundle::setColorPair(Trundle::highlightColorPair());
        }
        const auto& text = _model->rowText(i);
        Trundle::print(text);
        if (i == _selectedRow) {
            Trundle::setColorPair(Trundle::defaultColorPair());
        } else {
            Trundle::print(String::Space);
        }
    }
}

}
