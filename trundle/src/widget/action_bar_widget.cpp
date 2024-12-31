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

    auto wideDividerH = addChild<DividerWidget>();
    wideDividerH->addLayoutConstraint({LayoutAttribute::Left, this, LayoutAttribute::Left, -1});
    wideDividerH->addLayoutConstraint({LayoutAttribute::Right, this, LayoutAttribute::Right, 1});
    wideDividerH->addLayoutConstraint({LayoutAttribute::Bottom, this, LayoutAttribute::Top});
    wideDividerH->addLayoutConstraint({LayoutAttribute::Height, 1});
    wideDividerH->setDividerOrientation(DividerOrientation::Horizontal);
}

auto ActionBarWidget::displayActions(const std::vector<std::unique_ptr<Action>>& actions) -> void {
    for (const auto& action : actions) {
        _displayActions.push_back(action.get());
    }
}

auto ActionBarWidget::focusChanged() -> void {
    setVisible(focused());
    parent()->queueRecalculateLayoutConstraints();
}

auto ActionBarWidget::actionsSize() const -> int {
    return static_cast<int>(_displayActions.size());
}

auto ActionBarWidget::cols() const -> int {
    return std::min(size().x / ActionWidth, static_cast<int>(_displayActions.size()));
}

auto ActionBarWidget::render() const noexcept -> void {
    if (!cols()) {
        return;
    }

    auto col = 0;
    auto row = 0;

    const auto colWidth = size().x / cols();

    for (const auto& action : _displayActions) {
        Trundle::moveCursor({pos().x + col * colWidth + 1, pos().y + row});
        Trundle::setColorPair(Trundle::highlightColorPair());
        Trundle::print(keyToString(action->key));
        Trundle::setColorPair(Trundle::defaultColorPair());
        Trundle::print(String::Space);
        Trundle::print(action->title);

        ++col;
        if (pos().x + col * colWidth + colWidth > layoutAttributeValue(LayoutAttribute::Right).value().result) {
            col = 0;
            ++row;
        }
    }
}
}