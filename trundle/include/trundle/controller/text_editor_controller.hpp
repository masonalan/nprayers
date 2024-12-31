//
// Created by James Pickering on 12/30/24.
//

#pragma once

#include <trundle/controller/controller.hpp>

#include <string>

namespace trundle {

struct ActionBarWidget;
struct FrameWidget;
struct TextFieldWidget;
struct Widget;

struct TextEditorController : public Controller {
    TextEditorController(Controller* parent);

    auto setTitle(const std::string& title) -> void;

    [[nodiscard]] auto mainWidget() -> Widget* override;
    [[nodiscard]] auto frame() -> FrameWidget*;
    [[nodiscard]] auto textEditor() -> TextFieldWidget*;
    [[nodiscard]] auto actionBar() -> ActionBarWidget*;

private:
    FrameWidget* _frameWidget;
    TextFieldWidget* _textFieldWidget;
    ActionBarWidget* _actionsWidget;
};

}
