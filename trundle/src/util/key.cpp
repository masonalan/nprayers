//
// Created by James Pickering on 12/28/24.
//

#include <trundle/util/key.hpp>

#include <trundle/util/unicode.hpp>

namespace trundle {

auto keyToString(Key key) -> const std::wstring& {
    switch (key) {
    case Key::CtrlA:
        return KeyStr::CtrlA;
    case Key::CtrlB:
        return KeyStr::CtrlB;
    case Key::CtrlD:
        return KeyStr::CtrlD;
    case Key::CtrlE:
        return KeyStr::CtrlE;
    case Key::CtrlF:
        return KeyStr::CtrlF;
    case Key::CtrlG:
        return KeyStr::CtrlG;
    case Key::CtrlH:
        return KeyStr::CtrlH;
    case Key::CtrlI:
        return KeyStr::CtrlI;
    case Key::CtrlK:
        return KeyStr::CtrlK;
    case Key::CtrlL:
        return KeyStr::CtrlL;
    case Key::CtrlN:
        return KeyStr::CtrlN;
    case Key::CtrlP:
        return KeyStr::CtrlP;
    case Key::CtrlR:
        return KeyStr::CtrlR;
    case Key::CtrlT:
        return KeyStr::CtrlT;
    case Key::CtrlU:
        return KeyStr::CtrlU;
    case Key::CtrlW:
        return KeyStr::CtrlW;
    case Key::CtrlX:
        return KeyStr::CtrlX;
    case Key::Delete:
        return KeyStr::Delete;
    case Key::Down:
        return KeyStr::Down;
    case Key::Enter:
        return KeyStr::Enter;
    case Key::Escape:
        return KeyStr::Escape;
    case Key::Left:
        return KeyStr::Left;
    case Key::OptLeft:
        return KeyStr::OptLeft;
    case Key::OptO:
        return KeyStr::OptO;
    case Key::OptQ:
        return KeyStr::OptQ;
    case Key::OptR:
        return KeyStr::OptR;
    case Key::OptRight:
        return KeyStr::OptRight;
    case Key::OptS:
        return KeyStr::OptS;
    case Key::Right:
        return KeyStr::Right;
    case Key::ShiftDown:
        return KeyStr::ShiftDown;
    case Key::ShiftLeft:
        return KeyStr::ShiftLeft;
    case Key::ShiftRight:
        return KeyStr::ShiftRight;
    case Key::ShiftUp:
        return KeyStr::ShiftUp;
    case Key::ShiftTab:
        return KeyStr::ShiftTab;
    case Key::Space:
        return KeyStr::Space;
    case Key::Tab:
        return KeyStr::Tab;
    case Key::Up:
        return KeyStr::Up;
    default:
        return KeyStr::None;
    }
}

}