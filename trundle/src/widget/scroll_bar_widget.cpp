//
// Created by James Pickering on 1/3/25.
//

#include <trundle/widget/scroll_bar_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/widget/label_widget.hpp>

namespace trundle {

ScrollBarWidget::ScrollBarWidget(Widget* parent) :
    Widget{parent} {
    auto topLabel = addChild<LabelWidget>();
    topLabel->setText(Unicode::TriangleUp);

    auto bottomLabel = addChild<LabelWidget>();
    bottomLabel->setText(Unicode::TriangleDown);

    topLabel->addLayoutConstraints({{LayoutAttr::Width, 1},
                                    {LayoutAttr::Height, 1},
                                    {LayoutAttr::Left, this, LayoutAttr::Left},
                                    {LayoutAttr::Top, this, LayoutAttr::Top}});

    bottomLabel->addLayoutConstraints({{LayoutAttr::Width, 1},
                                       {LayoutAttr::Height, 1},
                                       {LayoutAttr::Left, this, LayoutAttr::Left},
                                       {LayoutAttr::Bottom, this, LayoutAttr::Bottom}});

    addLayoutConstraint({LayoutAttr::Width, 1});
}

auto ScrollBarWidget::setContentHeight(int height) -> void {
    _contentHeight = height;
    if (layoutResolved()) {
        setScrollOffset(_scrollOffset);
    }
}

auto ScrollBarWidget::setScrollOffset(int offset) -> void {
    if (!layoutResolved()) {
        return;
    }

    const auto maxHeight = size().y - 2;
    const auto totalSteps = _contentHeight < size().y ? 0 : _contentHeight - size().y;
    const auto barHeight = totalSteps > maxHeight ? 1 : maxHeight - totalSteps;
    const auto steps = maxHeight - barHeight;

    _scrollOffset = static_cast<int>(static_cast<double>(offset) / static_cast<double>(totalSteps) * static_cast<double>(steps));

    setVisible(barHeight < maxHeight);
}

auto ScrollBarWidget::render() const -> void {
    const auto maxHeight = size().y - 2;
    const auto totalSteps = _contentHeight < size().y ? 0 : _contentHeight - size().y;
    const auto barHeight = totalSteps > maxHeight ? 1 : maxHeight - totalSteps;

    for (auto i = _scrollOffset + 1; i <= barHeight + _scrollOffset; ++i) {
        Trundle::moveCursor({pos().x, pos().y + i});
        Trundle::print(Unicode::BlockMediumShade);
    }
}

auto ScrollBarWidget::willAppear() -> void {
    setScrollOffset(_scrollOffset);
}

}