//
// Created by James Pickering on 12/30/24.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

namespace trundle {

struct ActionBarWidget;
struct ListView;
struct ListWidget;
struct Widget;

enum class ListViewFlag : uint8_t {
    None = 0,
    Editable = 1 << 0,
};

using ListViewCallback = std::function<void(ListView*, int)>;

struct ListView final : FrameWidget {
    explicit ListView(Widget* parent = nullptr);

    auto setFlags(ListViewFlag flags) -> void;
    auto setOnAdd(ListViewCallback&& fn) -> void;
    auto setOnRemove(ListViewCallback&& fn) -> void;

    [[nodiscard]] auto list() const -> ListWidget*;
    [[nodiscard]] auto actionBar() const -> ActionBarWidget*;

private:
    ListWidget* _list;
    ActionBarWidget* _actionBar;

    ListViewCallback _addCallback{nullptr};
    ListViewCallback _removeCallback{nullptr};
};

}