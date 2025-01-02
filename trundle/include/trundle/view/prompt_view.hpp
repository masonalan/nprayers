//
// Created by James Pickering on 1/1/25.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

#include <string>

namespace trundle {

struct ActionBarWidget;
struct FrameWidget;
struct LabelWidget;
struct PromptView;
struct TextFieldWidget;
struct WindowWidget;

using PromptCallback = std::function<void(PromptView*)>;

struct PromptView final : FrameWidget {
    explicit PromptView(Widget* parent = nullptr);

    auto setMessage(const std::wstring& message) -> void;
    auto setValue(const std::wstring& value) const -> void;
    auto setPlaceholder(const std::wstring& placeholder) -> void;
    auto setOnAccept(PromptCallback&& callback) -> void;
    auto setOnReject(PromptCallback&& callback) -> void;
    auto setTextFieldVisible(bool visible) const -> void;

    [[nodiscard]] auto message() const -> const std::wstring&;
    [[nodiscard]] auto value() const -> const std::wstring&;
    [[nodiscard]] auto window() -> WindowWidget*;

protected:
    auto update() -> void override;
    auto render() const noexcept -> void override;
    auto focusChanged() -> void override;

private:
    std::wstring _message;
    std::wstring _placeholder;

    TextFieldWidget* _textField;
    ActionBarWidget* _actionBar;
    LabelWidget* _arrowLabel;
    LabelWidget* _messageLabel;

    PromptCallback _onAccept{nullptr};
    PromptCallback _onReject{nullptr};
};

struct Prompt {
    static auto create(WindowWidget* window,
                   const std::string& title,
                   const std::wstring& message,
                   PromptCallback&& onAccept,
                   PromptCallback&& onReject) -> PromptView*;

    static auto createWithTextField(WindowWidget* window,
                                    const std::string& title,
                                    const std::wstring& message,
                                    const std::wstring& placeholder,
                                    PromptCallback&& onAccept,
                                    PromptCallback&& onReject) -> PromptView*;
};

}
