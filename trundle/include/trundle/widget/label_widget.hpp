//
// Created by James Pickering on 1/2/25.
//

#pragma once

#include <trundle/util/text.hpp>
#include <trundle/widget/widget.hpp>

#include <string>

namespace trundle {

struct LabelWidget final : Widget {
    using Widget::Widget;

    auto setText(const std::wstring& text) -> void;

    [[nodiscard]] auto text() const -> const std::wstring&;

protected:
    auto willAppear() -> void override;
    auto render() const noexcept -> void override;

private:
    WrappingText _wrapper;
};

}