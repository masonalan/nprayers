//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/widget/widget.hpp>

namespace trundle {

struct TextAreaWidget : public Widget {
    using Widget::Widget;

    auto setText(const std::string& text) -> void;

protected:
    auto render() const noexcept -> void override;

private:
    std::string _text{};
};

}
