//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/util/layout_attribute.hpp>
#include <trundle/util/layout_constraint.hpp>

#include <glm/glm.hpp>

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

namespace trundle {

struct Action;

// Widget
struct Widget {
    explicit Widget(Widget* parent = nullptr);
    ~Widget();

    auto performUpdate() -> void;
    auto performRender() const -> void;

    auto addLayoutConstraint(LayoutConstraint&& constraint) -> void;
    auto queueRecalculateLayoutConstraints() -> void;

    auto setFocused(bool focused) -> void;
    auto setVisible(bool visible) -> void;

    [[nodiscard]] auto parent() -> Widget*;
    [[nodiscard]] auto parent() const -> Widget*;
    [[nodiscard]] auto pos() const -> glm::ivec2;
    [[nodiscard]] auto size() const -> glm::ivec2;
    [[nodiscard]] auto layoutAttributeValue(LayoutAttribute attr) const -> std::optional<LayoutAttributeValue>;
    [[nodiscard]] auto layoutResolved() const -> bool;
    [[nodiscard]] auto focused() const -> bool;
    [[nodiscard]] auto visible() const -> bool;
    [[nodiscard]] auto children() const -> const std::vector<std::unique_ptr<Widget>>&;
    [[nodiscard]] auto actions() const -> const std::vector<std::unique_ptr<Action>>&;

    template <typename T, typename... Args>
    auto addChild(Args&&... args) -> T* {
        static_assert(std::is_base_of_v<Widget, T>);
        _children.push_back(std::make_unique<T>(this, std::forward<Args>(args)...));
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

protected:
    virtual auto update() -> void;
    virtual auto render() const noexcept -> void;
    virtual auto clear() const noexcept -> void;
    virtual auto focusChanged() -> void;
    virtual auto childAdded() -> void;
    virtual auto willAppear() -> void;

private:
    auto setLayoutAttributeValue(LayoutAttribute attr, LayoutAttributeValue value) -> void;
    auto recalculateLayoutAttributeValues() -> void;
    auto beginListeningForActions() -> void;
    auto endListeningForActions() -> void;

    std::vector<std::unique_ptr<Widget>> _children;
    std::vector<std::unique_ptr<Action>> _actions;
    std::vector<LayoutConstraint> _constraints;
    std::unordered_map<LayoutAttribute, LayoutAttributeValue> _values;

    Widget* _parent;

    bool _focused{};
    bool _visible{};
    bool _rendered = false;
    bool _layoutDirty = false;
    unsigned int _actionListenerId = 0;
};

}