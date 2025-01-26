//
// Created by James Pickering on 12/23/24.
//

#include <trundle/widget/widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/action.hpp>
#include <trundle/util/layout_constraint_result.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/widget/window_widget.hpp>

#include <unordered_map>
#include <vector>

namespace trundle {

static auto requiredLayoutAttributes(LayoutAttr attr) {
    switch (attr) {
    case LayoutAttr::Right:
        return std::vector{LayoutAttr::Left, LayoutAttr::Width};
    case LayoutAttr::Left:
        return std::vector{LayoutAttr::Right, LayoutAttr::Width};
    case LayoutAttr::Top:
        return std::vector{LayoutAttr::Bottom, LayoutAttr::Height};
    case LayoutAttr::Bottom:
        return std::vector{LayoutAttr::Top, LayoutAttr::Height};
    default:
        return std::vector<LayoutAttr>{};
    }
}

Widget::Widget(Widget* parent) :
    _parent{parent},
    _window{[&parent]() {
        if (const auto w = dynamic_cast<ScreenWidget*>(parent)) {
            return w;
        }
        if (parent) {
            return parent->window();
        }
        return static_cast<ScreenWidget*>(nullptr);
    }()} {
    setFocused(parent != nullptr && parent->focused());
    setVisible(parent == nullptr || parent->visible());
}

Widget::~Widget() = default;

auto Widget::performUpdate() -> void {// NOLINT
    update();

    if (_layoutDirty) {
        recalculateLayoutAttributeValues();
        _layoutDirty = false;
    }

    if (layoutResolved()) {
        if (visible() && !_appeared) {
            willAppear();
            _appeared = true;
        } else if (!visible() && _appeared) {
            willDisappear();
            _appeared = false;
        }
    }

    for (auto& child : _children) {
        child->performUpdate();
    }
}

auto Widget::performRender() const -> void {// NOLINT
    if (!layoutResolved()) {
        auto msg = std::string{"Not all layout attributes are set. Attributes (" + std::to_string(_values.size()) + "): "};
        for (const auto& [attr, val] : _values) {
            msg.append(layoutAttributeToString(attr));
            msg.append(":");
            msg.append(std::to_string(val.result));
            msg.append(", ");
        }
        Trundle::end();
        throw std::runtime_error(msg);
    }

    if (!visible()) {
        return;
    }

    Trundle::moveCursor(pos());
    render();

    for (const auto& child : _children) {
        child->performRender();
    }
}

auto Widget::addLayoutConstraint(LayoutConstraint&& constraint) -> void {
    _constraints.push_back(constraint);
    _layoutDirty = true;
}

auto Widget::addLayoutConstraints(std::vector<LayoutConstraint>&& constraints) -> void {
    for (auto& constraint : constraints) {
        _constraints.push_back(constraint);
    }
    _layoutDirty = true;
}

auto Widget::queueRecalculateLayoutConstraints() -> void {
    _layoutDirty = true;
    for (auto& child : _children) {
        child->queueRecalculateLayoutConstraints();
    }
}

auto Widget::setFocused(bool focused) -> void {// NOLINT
    _focused = focused;
    if (!_actions.empty()) {
        if (focused) {
            beginListeningForActions();
        } else {
            endListeningForActions();
        }
    }
    focusChanged();
    for (const auto& child : _children) {
        if (!focused || !dynamic_cast<FrameWidget*>(child.get())) {
            child->setFocused(focused);
        }
    }
}

auto Widget::setVisible(bool visible) -> void {// NOLINT
    _visible = visible;
    if (!_visible) {
        clear();
    }
    for (const auto& child : _children) {
        child->setVisible(visible);
    }
}

auto Widget::clearActions() -> void {
    _actions.clear();
}

auto Widget::parent() -> Widget* {
    return _parent;
}

auto Widget::parent() const -> Widget* {
    return _parent;
}

auto Widget::pos() const -> glm::ivec2 {
    return glm::ivec2{
        layoutAttributeValue(LayoutAttr::Left).value().result,
        layoutAttributeValue(LayoutAttr::Top).value().result};
}

auto Widget::size() const -> glm::ivec2 {
    return glm::ivec2{
        layoutAttributeValue(LayoutAttr::Width).value().result,
        layoutAttributeValue(LayoutAttr::Height).value().result};
}

auto Widget::setLayoutAttributeValue(LayoutAttr attr, LayoutAttributeValue value) -> void {// NOLINT
    if (!visible()) {
        if (value.priority == LayoutAttributeValuePriority::Explicit) {
            if (attr == LayoutAttr::Height || attr == LayoutAttr::Width) {
                value.result = 0;
            } else {
                if (value.relative) {
                    value.result = value.xWidgetValue;
                } else {
                    value.result = 0;
                }
            }
        }
    }
    _values[attr] = value;

    auto setImplicitValues = [this, &value](LayoutAttr attr1, LayoutAttr attr2, auto&& result1Fn, auto&& result2Fn) {// NOLINT
        const auto& value1 = layoutAttributeValue(attr1);
        const auto& value2 = layoutAttributeValue(attr2);
        if (layoutAttributeValueNotSetOrImplicit(value1) && value2.has_value()) {
            setLayoutAttributeValue(attr1, {result1Fn(value.result, value2.value().result), LayoutAttributeValuePriority::Implicit});
        } else if (layoutAttributeValueNotSetOrImplicit(value2) && value1.has_value()) {
            setLayoutAttributeValue(attr2, {result2Fn(value.result, value1.value().result), LayoutAttributeValuePriority::Implicit});
        }
    };

    switch (attr) {
    case LayoutAttr::Left: {
        setImplicitValues(
            LayoutAttr::Right,
            LayoutAttr::Width,
            [](auto left, auto width) { return left + width; },
            [](auto left, auto right) { return right - left; });
        break;
    }
    case LayoutAttr::Right: {
        setImplicitValues(
            LayoutAttr::Left,
            LayoutAttr::Width,
            [](auto right, auto width) { return right - width; },
            [](auto right, auto left) { return right - left; });
        break;
    }
    case LayoutAttr::Top: {
        setImplicitValues(
            LayoutAttr::Bottom,
            LayoutAttr::Height,
            [](auto top, auto height) { return top + height; },
            [](auto top, auto bottom) { return bottom - top; });
        break;
    }
    case LayoutAttr::Bottom: {
        setImplicitValues(
            LayoutAttr::Top,
            LayoutAttr::Height,
            [](auto bottom, auto height) { return bottom - height; },
            [](auto bottom, auto top) { return bottom - top; });
        break;
    }
    case LayoutAttr::Width: {
        setImplicitValues(
            LayoutAttr::Left,
            LayoutAttr::Right,
            [](auto width, auto right) { return right - width; },
            [](auto width, auto left) { return left + width; });
        break;
    }
    case LayoutAttr::Height: {
        setImplicitValues(
            LayoutAttr::Top,
            LayoutAttr::Bottom,
            [](auto height, auto bottom) { return bottom - height; },
            [](auto height, auto top) { return height + top; });
        break;
    }
    default:
        break;
    }
}

auto Widget::layoutAttributeValue(trundle::LayoutAttr attr) const -> std::optional<LayoutAttributeValue> {
    if (_values.count(attr)) {
        return _values.at(attr);
    }
    return std::nullopt;
}

auto Widget::layoutResolved() const -> bool {
    for (auto i = 0; i < static_cast<std::underlying_type_t<LayoutAttr>>(LayoutAttr::None); ++i) {
        if (!_values.count(static_cast<LayoutAttr>(i))) {
            return false;
        }
    }
    return true;
}

auto Widget::focused() const -> bool {
    return _focused;
}

auto Widget::visible() const -> bool {
    return _visible;
}

auto Widget::children() const -> const std::vector<std::unique_ptr<Widget>>& {
    return _children;
}

auto Widget::actions() const -> const std::vector<std::unique_ptr<Action>>& {
    return _actions;
}

auto Widget::window() const -> ScreenWidget* {
    return _window;
}

auto Widget::recalculateLayoutAttributeValues() -> void {
    for (auto& c : _constraints) {
        if (!c.xWidget) {
            setLayoutAttributeValue(c.yAttr, {static_cast<int>(c.constantFn ? c.constantFn(this) : c.constant), LayoutAttributeValuePriority::Explicit, false, 0});
        } else if (const auto val = c.xWidget->layoutAttributeValue(c.xAttr); val.has_value()) {
            if (c.constantFnAttr) {
                setLayoutAttributeValue(c.yAttr, {static_cast<int>(c.constantFnAttr(this, c.xWidget, val.value().result)), LayoutAttributeValuePriority::Explicit, true, val.value().result});
            } else {
                setLayoutAttributeValue(c.yAttr, {static_cast<int>(val.value().result * c.multiplier + c.constant), LayoutAttributeValuePriority::Explicit, true, static_cast<int>(val.value().result)});
            }
        }
    }
}

auto Widget::recalculateLayout() -> void {// NOLINT
    clear();
    recalculateLayoutAttributeValues();
    for (const auto& child : _children) {
        child->recalculateLayout();
    }
}

auto Widget::beginListeningForActions() -> void {
    if (!_actionListenerId) {
        _actionListenerId = Keyboard::addListener([this](auto& event) {
            for (const auto& action : _actions) {
                if (Keyboard::currKey() == action->key) {
                    action->callback(this);
                    event.accept();
                    break;
                }
            }
        });
    }
}

auto Widget::endListeningForActions() -> void {
    if (_actionListenerId) {
        Keyboard::removeListener(_actionListenerId);
        _actionListenerId = 0;
    }
}

auto Widget::update() -> void {
}

auto Widget::render() const -> void {
}

auto Widget::focusChanged() -> void {
}

auto Widget::childAdded() -> void {
}

auto Widget::willAppear() -> void {
}

auto Widget::willDisappear() -> void {
}

auto Widget::clear() const noexcept -> void {
    if (!layoutResolved()) {
        return;
    }

    for (auto row = 0; row < size().y; ++row) {
        Trundle::moveCursor({pos().x, pos().y + row});
        for (auto col = 0; col < size().x; ++col) {
            Trundle::print(String::Space);
        }
    }
}

}
