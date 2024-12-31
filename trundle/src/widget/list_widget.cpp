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
    addAction(Key::Up, "Up", [this](auto _) {
        const auto newSel = std::max(_selectedRow - 1, 0);
        if (newSel != _selectedRow) {
            _selectedRow = newSel;
            if (_selectionChangedCallback) {
                _selectionChangedCallback(this, _selectedRow);
            }
        }
    });
    addAction(Key::Down, "Down", [this](auto _) {
        const auto newSel = std::min(_selectedRow + 1, static_cast<int>(_model->rowCount()) - 1);
        if (newSel != _selectedRow) {
            _selectedRow = newSel;
            if (_selectionChangedCallback) {
                _selectionChangedCallback(this, _selectedRow);
            }
        }
    });
    addAction(Key::OptR, "Add", [this](auto _) {
        if (_addCallback) {
            _addCallback(this, _selectedRow);
        }
        clear();
    });
    addAction(Key::Delete, "Remove", [this](auto _) {
        if (_removeCallback) {
            _removeCallback(this, _selectedRow);
        }
        clear();
    });
}

auto ListWidget::addItem(std::string item) -> void {
    _items.push_back(std::move(item));
    clear();
}

auto ListWidget::selectRow(int row) -> void {
    _selectedRow = row;
}

auto ListWidget::setAddCallback(std::function<void(ListWidget*, int)>&& fn) -> void {
    _addCallback = fn;
}

auto ListWidget::setRemoveCallback(std::function<void(ListWidget*, int)>&& fn) -> void {
    _removeCallback = fn;
}

auto ListWidget::setSelectionChangedCallback(std::function<void(const ListWidget*, int)>&& fn) -> void {
    _selectionChangedCallback = fn;
}

auto ListWidget::focusChanged() -> void {
//    if (focused()) {
//        Keyboard::addListener(this, [this](auto& event) {
//            keyPressed();
//        });
//    } else {
//        Keyboard::removeListener(this);
//    }
}

auto ListWidget::selectedRow() const -> int {
    return _selectedRow;
}

auto ListWidget::rowCount() const -> int {
    return static_cast<int>(_items.size());
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
