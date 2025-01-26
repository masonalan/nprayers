//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

#include <string>
#include <vector>

namespace trundle {

struct PickerWidget : public FrameWidget {
    explicit PickerWidget(Widget* parent = nullptr);

    auto setOptions(const std::vector<std::wstring>& options) -> void;

protected:
    auto update() -> void override;
    auto render() const -> void override;

private:
    std::vector<std::wstring> _options{};
    int _currOption = 0;
};

}