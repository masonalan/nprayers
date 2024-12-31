//
// Created by James Pickering on 11/17/24.
//

#pragma once

#include <trundle/util/key.hpp>

#include <functional>
#include <string>

namespace trundle {

struct Widget;

struct KeyboardEvent {
    auto accept() -> void;

    [[nodiscard]] auto accepted() const -> bool;

private:
    bool _accepted{false};
};

struct Keyboard {
    static auto init() -> void;
    static auto poll() -> void;
    static auto currKey() -> Key;
    static auto currChar() -> char;
    static auto addListener(std::function<void(KeyboardEvent&)>&& callback) -> unsigned int;
    static auto removeListener(unsigned int id) -> void;
};

}
