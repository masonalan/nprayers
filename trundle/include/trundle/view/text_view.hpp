//
// Created by James Pickering on 12/30/24.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

namespace trundle {

struct ActionBarWidget;
struct FrameWidget;
struct TextFieldWidget;
struct Widget;

struct TextView final : FrameWidget {
    explicit TextView(Widget* parent = nullptr);

    [[nodiscard]] auto textField() const -> TextFieldWidget*;

private:
    TextFieldWidget* _field;
};

}
