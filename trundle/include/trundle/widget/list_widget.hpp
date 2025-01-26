//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include "trundle/model/model.hpp"
#include "trundle/renderer/header_render_delegate.hpp"
#include "trundle/renderer/item_render_delegate.hpp"

#include <trundle/model/list_model.hpp>
#include <trundle/util/key.hpp>
#include <trundle/widget/widget.hpp>

#include <string>
#include <vector>

namespace trundle {

struct ListWidget;
struct Model;
struct HeaderRenderDelegate;
struct ItemRenderDelegate;

using SelectionChangedCallback = std::function<void(const ListWidget*, int, int)>;

struct ListWidget : Widget {
    explicit ListWidget(Widget* parent);

    auto setModel(Model* model) -> void;
    auto setUpKey(Key key) -> void;
    auto setDownKey(Key key) -> void;
    auto addItem(std::string item) -> void;
    auto selectRow(int row) -> void;

    auto setOnSelectionChanged(SelectionChangedCallback&& fn) -> void;
    auto setHeaderRenderDelegate(HeaderRenderDelegate* delegate) -> void;
    auto setItemRenderDelegate(ItemRenderDelegate* delegate) -> void;

    [[nodiscard]] auto selectedRow() const -> int;
    [[nodiscard]] auto rowCount() const -> int;
    [[nodiscard]] auto model() const -> Model*;

protected:
    auto update() -> void override;
    auto render() const -> void override;

private:
    Model* _model{nullptr};
    Key _upKey{Key::Up};
    Key _downKey{Key::Down};
    std::vector<std::string> _items{};
    int _selectedRow{};

    SelectionChangedCallback _selectionChangedCallback{nullptr};

    HeaderRenderDelegate* _headerRenderDelegate;
    ItemRenderDelegate* _itemRenderDelegate;
};

}