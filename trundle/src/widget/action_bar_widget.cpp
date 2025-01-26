//
// Created by James Pickering on 12/23/24.
//

#include <trundle/widget/action_bar_widget.hpp>

#include "trundle/widget/divider_widget.hpp"
#include <trundle/trundle.hpp>
#include <trundle/util/unicode.hpp>

namespace trundle {

constexpr static auto ActionWidth = 10;

ActionBarWidget::ActionBarWidget(Widget* parent) :
    Widget{parent} {
    setVisible(focused());

    // _divider = addChild<DividerWidget>();
    // _divider->addLayoutConstraint({LayoutAttribute::Left, this, LayoutAttribute::Left});
    // _divider->addLayoutConstraint({LayoutAttribute::Right, this, LayoutAttribute::Right});
    // _divider->addLayoutConstraint({LayoutAttribute::Bottom, this, LayoutAttribute::Top});
    // _divider->addLayoutConstraint({LayoutAttribute::Height, 1});
    // _divider->setDividerOrientation(DividerOrientation::Horizontal);
    // _divider->setVisible(focused() && !_displayActions.empty());

    addLayoutConstraint({LayoutAttr::Left, parent, LayoutAttr::Left, 1});
    addLayoutConstraint({LayoutAttr::Right, parent, LayoutAttr::Right, -1});
    addLayoutConstraint({LayoutAttr::Bottom, parent, LayoutAttr::Bottom});
    addLayoutConstraint({LayoutAttr::Height, this, LayoutAttr::Width, [this](auto, auto, auto v) {
                             if (!this->visible()) {
                                 return 0.0;
                             }
                             const auto cols = v / 10;
                             const auto count = this->actionsSize() - 1;
                             return static_cast<double>(count / cols + 2);
                         }});
}

auto ActionBarWidget::displayActions(const std::vector<std::unique_ptr<Action>>& actions) -> void {
    _displayActions.clear();
    for (const auto& action : actions) {
        _displayActions.push_back(action.get());
    }
    // _divider->setVisible(focused() && !_displayActions.empty());
    // _divider->setVisible(false);
}

auto ActionBarWidget::focusChanged() -> void {
    // setVisible(focused());
    // parent()->queueRecalculateLayoutConstraints();
    // _divider->setVisible(focused() && !_displayActions.empty());
    // _divider->setVisible(false);
}

auto ActionBarWidget::actionsSize() const -> int {
    return static_cast<int>(_displayActions.size());
}

auto ActionBarWidget::cols() const -> int {
    return std::min(size().x / ActionWidth, static_cast<int>(_displayActions.size()));
}

auto ActionBarWidget::render() const -> void {
    if (!cols()) {
        return;
    }

    auto col = 0;
    auto row = 0;

    const auto colWidth = size().x / cols();

    for (const auto& action : _displayActions) {
        Trundle::moveCursor({pos().x + col * colWidth + 1, pos().y + row});
        Trundle::setColorPair(Trundle::focusHighlightColorPair());
        Trundle::print(keyToString(action->key));
        Trundle::setColorPair(Trundle::defaultColorPair());
        Trundle::print(String::Space);
        Trundle::print(action->title);

        ++col;
        if (pos().x + col * colWidth + colWidth > layoutAttributeValue(LayoutAttr::Right).value().result) {
            col = 0;
            ++row;
        }
    }
}
}