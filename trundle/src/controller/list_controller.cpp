//
// Created by James Pickering on 12/30/24.
//

#include <trundle/controller/list_controller.hpp>

#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/frame_widget.hpp>
#include <trundle/widget/list_widget.hpp>
#include <trundle/widget/widget.hpp>

namespace trundle {

ListController::ListController(Controller* parent) :
    _frameWidget{parent->mainWidget()->addChild<FrameWidget>()} {
    _frameWidget->setTitleBarStyle(TitleBarStyle::MultiLine);

    _actionsWidget = _frameWidget->addChild<ActionBarWidget>();
    _actionsWidget->addLayoutConstraint({LayoutAttribute::Left, _frameWidget, LayoutAttribute::Left});
    _actionsWidget->addLayoutConstraint({LayoutAttribute::Right, _frameWidget, LayoutAttribute::Right});
    _actionsWidget->addLayoutConstraint({LayoutAttribute::Bottom, _frameWidget, LayoutAttribute::Bottom});
    _actionsWidget->addLayoutConstraint({LayoutAttribute::Height, _actionsWidget, LayoutAttribute::Width, [this](auto width) {
                                             if (!_actionsWidget->visible()) {
                                                 return 0.0;
                                             }
                                             const auto cols = static_cast<int>(width) / 10;
                                             const auto count = _actionsWidget->actionsSize() - 1;
                                             return static_cast<double>(count / cols + 2);
                                         }});

    _listWidget = _frameWidget->addChild<ListWidget>();
    _listWidget->addLayoutConstraint({LayoutAttribute::Left, _frameWidget, LayoutAttribute::Left, 1});
    _listWidget->addLayoutConstraint({LayoutAttribute::Right, _frameWidget, LayoutAttribute::Right, -1});
    _listWidget->addLayoutConstraint({LayoutAttribute::Top, _frameWidget, LayoutAttribute::Top, 3});
    _listWidget->addLayoutConstraint({LayoutAttribute::Bottom, _actionsWidget, LayoutAttribute::Top});

    _actionsWidget->displayActions(_listWidget->actions());
}

auto ListController::mainWidget() -> Widget* {
    return _frameWidget;
}

auto ListController::frame() -> FrameWidget* {
    return _frameWidget;
}

auto ListController::list() -> ListWidget* {
    return _listWidget;
}

auto ListController::actionBar() -> ActionBarWidget* {
    return _actionsWidget;
}

}