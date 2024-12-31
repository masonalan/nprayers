//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/widget/widget.hpp>

#include <glm/glm.hpp>

#include <string>
#include <string_view>
#include <vector>

namespace trundle {

struct TextFieldWidget : public Widget {
    TextFieldWidget(Widget* parent = nullptr);

    auto setText(const std::string& text) -> void;

protected:
    auto update() -> void override;
    auto render() const noexcept -> void override;
    auto willAppear() -> void override;
//    auto keyPressed() -> void override;

private:
    auto updateTextLayout() -> void;
    auto moveCursor(glm::ivec2 delta) -> void;

    [[nodiscard]] auto charAtCursorPosition() const noexcept -> char;
    [[nodiscard]] auto iteratorAtCursorPosition() -> std::string::iterator;

    std::string _text{};
    glm::ivec2 _cursorPos{};
    std::vector<std::string_view> _rows{};
};

}