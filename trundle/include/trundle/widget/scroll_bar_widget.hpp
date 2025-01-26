//
// Created by James Pickering on 1/3/25.
//

#pragma once

#include <trundle/widget/widget.hpp>

namespace trundle {

struct ScrollBarWidget : Widget {
    explicit ScrollBarWidget(Widget* parent = nullptr);

    auto setContentHeight(int height) -> void;
    auto setScrollOffset(int offset) -> void;

protected:
    auto render() const -> void override;
    auto willAppear() -> void override;

private:
    int _contentHeight{};
    int _scrollOffset{0};
};

}
