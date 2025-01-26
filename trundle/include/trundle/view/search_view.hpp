//
// Created by James Pickering on 1/15/25.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

namespace trundle {

struct LabelWidget;
struct TextFieldWidget;

struct SearchView final : FrameWidget {
    explicit SearchView(Widget* parent = nullptr);

    [[nodiscard]] auto field() const -> TextFieldWidget*;

private:
    LabelWidget* _label;
    TextFieldWidget* _field;
};

}