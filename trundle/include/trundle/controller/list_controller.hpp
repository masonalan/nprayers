//
// Created by James Pickering on 12/30/24.
//

#pragma once

#include <trundle/controller/controller.hpp>

#include <string>

namespace trundle {

struct ActionBarWidget;
struct FrameWidget;
struct ListWidget;
struct Widget;

struct ListController : public Controller {
    ListController(Controller* parent);

    auto setTitle(const std::string& title) -> void;

    [[nodiscard]] auto mainWidget() -> Widget*;
    [[nodiscard]] auto frame() -> FrameWidget*;
    [[nodiscard]] auto list() -> ListWidget*;
    [[nodiscard]] auto actionBar() -> ActionBarWidget*;

private:
    FrameWidget* _frameWidget;
    ListWidget* _listWidget;
    ActionBarWidget* _actionsWidget;
};

}