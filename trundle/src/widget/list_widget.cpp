//
// Created by James Pickering on 12/26/24.
//

#include <trundle/widget/list_widget.hpp>

#include <trundle/model/item_model.hpp>
#include <trundle/renderer/abstract_header_render_delegate.hpp>
#include <trundle/renderer/list_item_render_delegate.hpp>
#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>

namespace trundle {

static auto defaultListItemRenderDelegate = std::make_unique<ListItemRenderDelegate>();
static auto defaultHeaderItemRenderDelegate = std::make_unique<AbstractHeaderRenderDelegate>();

ListWidget::ListWidget(trundle::Widget* parent) :
    Widget{parent} {
    setHeaderRenderDelegate(defaultHeaderItemRenderDelegate.get());
    setItemRenderDelegate(defaultListItemRenderDelegate.get());
}

auto ListWidget::setModel(Model* model) -> void {
    _model = model;
    _model->setOnDataChanged([this](auto) {
        clear();
    });
    _model->dataChanged();
}

auto ListWidget::setUpKey(Key key) -> void {
    _upKey = key;
}

auto ListWidget::setDownKey(Key key) -> void {
    _downKey = key;
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

auto ListWidget::setHeaderRenderDelegate(HeaderRenderDelegate* delegate) -> void {
    _headerRenderDelegate = delegate;
}

auto ListWidget::setItemRenderDelegate(ItemRenderDelegate* delegate) -> void {
    _itemRenderDelegate = delegate;
}

auto ListWidget::selectedRow() const -> int {
    return _selectedRow;
}

auto ListWidget::rowCount() const -> int {
    return static_cast<int>(_items.size());
}

auto ListWidget::model() const -> Model* {
    return _model;
}

auto ListWidget::update() -> void {
    if (focused()) {
        const auto currKey = Keyboard::currKey();
        if (currKey == _upKey) {
            if (const auto newRow = std::max(_selectedRow - 1, 0); newRow != _selectedRow) {
                const auto oldRow = _selectedRow;
                _selectedRow = newRow;
                if (_selectionChangedCallback) {
                    _selectionChangedCallback(this, oldRow, newRow);
                }
            }
        } else if (currKey == _downKey) {
            if (const auto newRow = std::min(_selectedRow + 1, static_cast<int>(_model->rowCount(_model->createIndex())) - 1); newRow != _selectedRow) {
                const auto oldRow = _selectedRow;
                _selectedRow = newRow;
                if (_selectionChangedCallback) {
                    _selectionChangedCallback(this, oldRow, newRow);
                }
                clear();
            }
        }
    }
}

void ListWidget::render() const {
    if (!_model) {
        return;
    }

    auto offset = 0;
    if (!_model->headerText().empty()) {
        offset += _headerRenderDelegate->render(this, {pos().x + 1, pos().y});
    }

    const auto rows = _model->rowCount(_model->createIndex());
    for (auto i = 0; i < rows; ++i) {
        const auto index = _model->index(_model->createIndex(), i);
        if (i == size().y) {
            break;
        }
        _itemRenderDelegate->render(this, index, {pos().x + 1, pos().y + offset}, i == _selectedRow, nullptr);
    }
}

}
