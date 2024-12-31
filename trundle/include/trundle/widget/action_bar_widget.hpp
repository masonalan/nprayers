//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/util/action.hpp>
#include <trundle/widget/widget.hpp>

#include <vector>

namespace trundle {

struct ActionBarWidget : Widget {
    explicit ActionBarWidget(Widget* parent = nullptr);

    auto displayActions(const std::vector<std::unique_ptr<Action>>& actions) -> void;

    [[nodiscard]] auto actionsSize() const -> int;
    [[nodiscard]] auto cols() const -> int;

protected:
    auto render() const noexcept -> void override;
    auto focusChanged() -> void override;

private:
    std::vector<Action*> _displayActions{};
    int _rows{};
};

}
