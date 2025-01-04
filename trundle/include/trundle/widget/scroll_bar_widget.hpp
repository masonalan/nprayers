//
// Created by James Pickering on 1/3/25.
//

#pragma once

#include <trundle/widget/widget.hpp>

namespace trundle {

struct ScrollBarWidget : Widget {
    explicit ScrollBarWidget(Widget* parent = nullptr);

    auto setContentHeight(unsigned int height) -> void;
    auto setScrollOffset(unsigned int offset) -> void;

protected:
    auto render() const noexcept -> void override;
    auto willAppear() -> void override;

private:
    unsigned int _contentHeight{};
    unsigned int _scrollOffset{0};
};

}
