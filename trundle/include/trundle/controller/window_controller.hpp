//
// Created by James Pickering on 12/30/24.
//

#pragma once

#include <trundle/controller/controller.hpp>

#include <memory>

namespace trundle {

struct WindowWidget;

struct WindowController : public Controller {
    explicit WindowController(std::string title);

    [[nodiscard]] auto mainWidget() -> Widget* override;

private:
    std::unique_ptr<WindowWidget> _mainWidget;
};

}
