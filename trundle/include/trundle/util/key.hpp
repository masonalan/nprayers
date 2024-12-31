//
// Created by James Pickering on 12/28/24.
//

#pragma once

#include <string>

namespace trundle {

enum class Key {
    Up,
    Down,
    Right,
    Left,
    Escape,
    Enter,
    OptO,
    OptQ,
    OptR,
    OptS,
    OptLeft,
    OptRight,
    Delete,
    Tab,
    ShiftTab,
    ShiftLeft,
    ShiftRight,
    None
};

struct KeyStr {
    static const std::string Up;
    static const std::string Down;
    static const std::string Right;
    static const std::string Left;
    static const std::string Escape;
    static const std::string Enter;
    static const std::string OptO;
    static const std::string OptQ;
    static const std::string OptR;
    static const std::string OptS;
    static const std::string OptLeft;
    static const std::string OptRight;
    static const std::string Delete;
    static const std::string Tab;
    static const std::string ShiftTab;
    static const std::string ShiftLeft;
    static const std::string ShiftRight;
    static const std::string None;
};

auto keyToString(Key key) -> const std::string&;

}
