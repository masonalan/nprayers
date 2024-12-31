//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/widget/widget.hpp>

#include <string>

enum class TitleBarStyle {
    SingleLine,
    DoubleLine,
    MultiLine,
    None
};

namespace trundle {

struct FrameWidget : public Widget {
    using Widget::Widget;

    auto setTitle(const std::string& title) -> void;
    auto setTitleBarStyle(TitleBarStyle style) -> void;

    [[nodiscard]] auto title() const -> const std::string&;
    [[nodiscard]] auto titleBarStyle() const -> TitleBarStyle;

protected:
    auto render() const noexcept -> void override;

private:
    std::string _title{};
    TitleBarStyle _titleBarStyle = TitleBarStyle::SingleLine;
};

}
