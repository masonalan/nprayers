//
// Created by James Pickering on 12/30/24.
//

#include <trundle/controller/window_controller.hpp>

#include <trundle/widget/window_widget.hpp>

namespace trundle {

WindowController::WindowController(std::string title) :
    _mainWidget{std::make_unique<WindowWidget>()} {
    _mainWidget->setTitle(title);
    _mainWidget->addLayoutConstraint({LayoutAttribute::Left, 2});
    _mainWidget->addLayoutConstraint({LayoutAttribute::Top, 1});
    _mainWidget->addLayoutConstraint({LayoutAttribute::Width, 150});
    _mainWidget->addLayoutConstraint({LayoutAttribute::Height, 55});
}

auto WindowController::mainWidget() -> Widget* {
    return _mainWidget.get();
}

};