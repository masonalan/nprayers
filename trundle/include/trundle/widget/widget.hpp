//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/util/layout_attribute.hpp>
#include <trundle/util/layout_constraint.hpp>

#include <glm/glm.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace trundle {

struct Action;
struct ScreenWidget;

struct Widget {
    explicit Widget(Widget* parent = nullptr);
    virtual ~Widget();

    auto performUpdate() -> void;
    auto performRender() const -> void;
    virtual auto clear() const noexcept -> void;

    auto addLayoutConstraint(LayoutConstraint&& constraint) -> void;
    auto addLayoutConstraints(std::vector<LayoutConstraint>&& constraints) -> void;
    auto queueRecalculateLayoutConstraints() -> void;

    auto setFocused(bool focused) -> void;
    auto setVisible(bool visible) -> void;

    auto clearActions() -> void;

    [[nodiscard]] auto parent() -> Widget*;
    [[nodiscard]] auto parent() const -> Widget*;
    [[nodiscard]] auto pos() const -> glm::ivec2;
    [[nodiscard]] auto size() const -> glm::ivec2;
    [[nodiscard]] auto layoutAttributeValue(LayoutAttr attr) const -> std::optional<LayoutAttributeValue>;
    [[nodiscard]] auto layoutResolved() const -> bool;
    [[nodiscard]] auto focused() const -> bool;
    [[nodiscard]] auto visible() const -> bool;
    [[nodiscard]] auto children() const -> const std::vector<std::unique_ptr<Widget>>&;
    [[nodiscard]] auto actions() const -> const std::vector<std::unique_ptr<Action>>&;
    [[nodiscard]] auto window() const -> ScreenWidget*;

    template <typename T, typename... Args>
    auto addChild(Args&&... args) -> T* {
        static_assert(std::is_base_of_v<Widget, T>);
        _children.push_back(std::make_unique<T>(std::forward<Args>(args)..., this));
        childAdded();
        return static_cast<T*>(_children.back().get());
    }

    template <typename... Args>
    auto addAction(Args&&... args) -> void {
        _actions.push_back(std::make_unique<Action>(std::forward<Args>(args)...));
        if (focused()) {
            beginListeningForActions();
        }
    }

    auto recalculateLayout() -> void;

protected:
    virtual auto update() -> void;
    virtual auto render() const -> void;

    virtual auto focusChanged() -> void;
    virtual auto childAdded() -> void;
    virtual auto willAppear() -> void;
    virtual auto willDisappear() -> void;

    auto recalculateLayoutAttributeValues() -> void;

private:
    auto setLayoutAttributeValue(LayoutAttr attr, LayoutAttributeValue value) -> void;
    auto beginListeningForActions() -> void;
    auto endListeningForActions() -> void;

    std::vector<std::unique_ptr<Widget>> _children;
    std::vector<std::unique_ptr<Action>> _actions;
    std::vector<LayoutConstraint> _constraints;
    std::unordered_map<LayoutAttr, LayoutAttributeValue> _values;

    Widget* _parent;
    ScreenWidget* _window;

    bool _focused{};
    bool _visible{};
    bool _appeared = false;
    bool _layoutDirty = false;
    unsigned int _actionListenerId = 0;
};

}