//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/model/list_model.hpp>
#include <trundle/widget/widget.hpp>

#include <string>
#include <vector>

namespace trundle {

struct ListWidget;

using SelectionChangedCallback = std::function<void(const ListWidget*, int, int)>;

struct ListWidget : public Widget {
    explicit ListWidget(Widget* parent);

    auto addItem(std::string item) -> void;
    auto selectRow(int row) -> void;

    auto setOnSelectionChanged(SelectionChangedCallback&& fn) -> void;

    [[nodiscard]] auto selectedRow() const -> int;
    [[nodiscard]] auto rowCount() const -> int;

    template <typename T, typename... Args>
    auto setModel(Args&&... args) {
        static_assert(std::is_base_of_v<ListModel, T>);
        _model = std::make_unique<T>(std::forward<Args>(args)...);
    }

protected:
    auto update() -> void override;
    auto render() const noexcept -> void override;

private:
    std::unique_ptr<ListModel> _model{nullptr};
    std::vector<std::string> _items{};
    int _selectedRow{};

    SelectionChangedCallback _selectionChangedCallback{nullptr};
};

}