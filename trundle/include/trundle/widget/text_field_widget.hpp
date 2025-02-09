//
// Created by James Pickering on 12/26/24.
//

#pragma once

#include <trundle/widget/widget.hpp>

#include <trundle/util/text.hpp>

#include <glm/glm.hpp>

#include <string>
#include <string_view>
#include <vector>

namespace trundle {

struct TextFieldWidget;
struct ScrollBarWidget;

using TextChangedCallback = std::function<void(TextFieldWidget*)>;

struct TextFieldWidget : Widget {
    explicit TextFieldWidget(Widget* parent = nullptr);

    auto setText(const std::wstring& text) -> void;
    auto setTextChanged(TextChangedCallback&& callback) -> void;
    auto setCursor(WrappingTextIterator cursor) -> void;

    auto scrollToEnd() -> void;

    [[nodiscard]] auto text() const -> const std::wstring&;
    [[nodiscard]] auto wrappedText() -> WrappingText&;

protected:
    auto update() -> void override;
    auto render() const -> void override;
    auto willAppear() -> void override;

private:
    auto updateTextLayout() -> void;
    auto moveCursor(Direction direction) -> void;

    glm::ivec2 _cursorPos{};
    WrappingTextIterator _cursor{};
    WrappingText _text{};
    TextChangedCallback _textChanged{nullptr};
    ScrollBarWidget* _scrollBar{nullptr};
    int _scrollOffset{};

};

}