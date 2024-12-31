//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/model/list_model.hpp>
#include <trundle/widget/widget.hpp>

#include <string>
#include <vector>

namespace trundle {

struct ListWidget : public Widget {
    explicit ListWidget(Widget* parent);

    auto addItem(std::string item) -> void;
    auto selectRow(int row) -> void;

    auto setAddCallback(std::function<void(ListWidget*, int)>&& fn) -> void;
    auto setRemoveCallback(std::function<void(ListWidget*, int)>&& fn) -> void;
    auto setSelectionChangedCallback(std::function<void(const ListWidget*, int)>&& fn) -> void;

    [[nodiscard]] auto selectedRow() const -> int;
    [[nodiscard]] auto rowCount() const -> int;

    template <typename T, typename... Args>
    auto setModel(Args&&... args) {
        static_assert(std::is_base_of_v<ListModel, T>);
        _model = std::make_unique<T>(std::forward<Args>(args)...);
    }

protected:
    auto render() const noexcept -> void override;
    auto focusChanged() -> void override;

private:
    std::unique_ptr<ListModel> _model{nullptr};
    std::vector<std::string> _items{};
    int _selectedRow{};

    std::function<void(ListWidget*, int)> _addCallback{nullptr};
    std::function<void(ListWidget*, int)> _removeCallback{nullptr};
    std::function<void(const ListWidget*, int)> _selectionChangedCallback{nullptr};

};

}