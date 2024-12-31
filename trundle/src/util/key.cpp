//
// Created by James Pickering on 12/28/24.
//

#include <trundle/util/key.hpp>

#include <trundle/util/unicode.hpp>

namespace trundle {

const std::string KeyStr::Up = Unicode::ArrowUp;
const std::string KeyStr::Down = Unicode::ArrowDown;
const std::string KeyStr::Right = Unicode::ArrowRight;
const std::string KeyStr::Left = Unicode::ArrowLeft;
const std::string KeyStr::Escape = "ESC";
const std::string KeyStr::Enter = Unicode::Return;
const std::string KeyStr::OptO = Unicode::Option + "O";
const std::string KeyStr::OptQ = Unicode::Option + "Q";
const std::string KeyStr::OptR = Unicode::Option + "R";
const std::string KeyStr::OptS = Unicode::Option + "S";
const std::string KeyStr::OptLeft = Unicode::Option + KeyStr::Left;
const std::string KeyStr::OptRight = Unicode::Option + KeyStr::Right;
const std::string KeyStr::Delete = "DEL";
const std::string KeyStr::Tab = Unicode::ArrowRightVertLine;
const std::string KeyStr::ShiftTab = Unicode::ArrowUpOutline + KeyStr::Tab;
const std::string KeyStr::ShiftLeft = Unicode::ArrowUpOutline + KeyStr::Left;
const std::string KeyStr::ShiftRight = Unicode::ArrowUpOutline + KeyStr::Right;
const std::string KeyStr::None = "";

auto keyToString(Key key) -> const std::string& {
    switch (key) {
    case Key::Up:
        return KeyStr::Up;
    case Key::Down:
        return KeyStr::Down;
    case Key::Right:
        return KeyStr::Right;
    case Key::Left:
        return KeyStr::Left;
    case Key::Escape:
        return KeyStr::Escape;
    case Key::Enter:
        return KeyStr::Enter;
    case Key::OptO:
        return KeyStr::OptO;
    case Key::OptQ:
        return KeyStr::OptQ;
    case Key::OptR:
        return KeyStr::OptR;
    case Key::OptS:
        return KeyStr::OptS;
    case Key::OptLeft:
        return KeyStr::OptLeft;
    case Key::OptRight:
        return KeyStr::OptRight;
    case Key::Delete:
        return KeyStr::Delete;
    case Key::Tab:
        return KeyStr::Tab;
    case Key::ShiftTab:
        return KeyStr::ShiftTab;
    case Key::ShiftLeft:
        return KeyStr::ShiftLeft;
    case Key::ShiftRight:
        return KeyStr::ShiftRight;
    case Key::None:
        return KeyStr::None;
    }
}

}