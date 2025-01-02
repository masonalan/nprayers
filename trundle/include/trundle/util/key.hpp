//
// Created by James Pickering on 12/28/24.
//

#pragma once

#include <trundle/util/unicode.hpp>

#include <string>

namespace trundle {

enum class Key {
    CtrlA,
    CtrlB,
    CtrlD,
    CtrlE,
    CtrlF,
    CtrlG,
    CtrlH,
    CtrlI,
    CtrlK,
    CtrlL,
    CtrlN,
    CtrlP,
    CtrlR,
    CtrlT,
    CtrlU,
    CtrlW,
    CtrlX,
    Delete,
    Down,
    Enter,
    Escape,
    Left,
    OptLeft,
    OptRight,
    OptO,
    OptQ,
    OptR,
    OptS,
    Right,
    ShiftTab,
    ShiftLeft,
    ShiftRight,
    Tab,
    Up,
    None
};

struct KeyStr {
    static constexpr std::wstring CtrlA = L"^A";
    static constexpr std::wstring CtrlB = L"^B";
    static constexpr std::wstring CtrlD = L"^D";
    static constexpr std::wstring CtrlE = L"^E";
    static constexpr std::wstring CtrlF = L"^F";
    static constexpr std::wstring CtrlG = L"^G";
    static constexpr std::wstring CtrlH = L"^H";
    static constexpr std::wstring CtrlI = L"^I";
    static constexpr std::wstring CtrlK = L"^K";
    static constexpr std::wstring CtrlL = L"^L";
    static constexpr std::wstring CtrlN = L"^N";
    static constexpr std::wstring CtrlP = L"^P";
    static constexpr std::wstring CtrlR = L"^R";
    static constexpr std::wstring CtrlT = L"^T";
    static constexpr std::wstring CtrlU = L"^U";
    static constexpr std::wstring CtrlW = L"^W";
    static constexpr std::wstring CtrlX = L"^X";
    static constexpr std::wstring Delete = L"⌫";
    static constexpr std::wstring Down = Unicode::ArrowDown;
    static constexpr std::wstring Enter = Unicode::Return;
    static constexpr std::wstring Escape = L"ESC";
    static constexpr std::wstring Left = Unicode::ArrowLeft;
    static constexpr std::wstring OptLeft = Unicode::Option + Left;
    static constexpr std::wstring OptO = Unicode::Option + L"O";
    static constexpr std::wstring OptQ = Unicode::Option + L"Q";
    static constexpr std::wstring OptR = Unicode::Option + L"R";
    static constexpr std::wstring OptRight = Unicode::Option + Unicode::ArrowRight;
    static constexpr std::wstring OptS = Unicode::Option + L"S";
    static constexpr std::wstring Right = Unicode::ArrowRight;
    static constexpr std::wstring ShiftLeft = Unicode::ArrowUpOutline + Left;
    static constexpr std::wstring ShiftRight = Unicode::ArrowUpOutline + Right;
    static constexpr std::wstring ShiftTab = Unicode::ArrowUpOutline + Unicode::ArrowRightVertLine;
    static constexpr std::wstring Tab = Unicode::ArrowRightVertLine;
    static constexpr std::wstring Up = Unicode::ArrowUp;
    static constexpr std::wstring None;
};

auto keyToString(Key key) -> const std::wstring&;

}
