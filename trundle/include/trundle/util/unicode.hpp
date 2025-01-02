//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <string>

namespace trundle {

struct String {
    static constexpr std::wstring Space = L" ";
};

struct Unicode {
    static constexpr std::wstring Block = L"█";
    static constexpr std::wstring BlockLeft = L"▌";
    static constexpr std::wstring BlockRight = L"▐";
    static constexpr std::wstring BlockTop = L"▀";
    static constexpr std::wstring BlockBottom = L"▄";
    static constexpr std::wstring BlockMediumShade = L"▒";
    static constexpr std::wstring BlockLightShade = L"░";
    static constexpr std::wstring Square = L"■";
    static constexpr std::wstring LineVert = L"│";
    static constexpr std::wstring LineHoriz = L"─";
    static constexpr std::wstring LineHorizDouble = L"═";
    static constexpr std::wstring CornerTopRight = L"┐";
    static constexpr std::wstring CornerTopRightHorizDouble = L"╕";
    static constexpr std::wstring CornerTopLeft = L"┌";
    static constexpr std::wstring CornerTopLeftHorizDouble = L"╒";
    static constexpr std::wstring CornerBottomRight = L"┘";
    static constexpr std::wstring CornerBottomLeft = L"└";
    static constexpr std::wstring ArrowRightDouble = L"»";
    static constexpr std::wstring Percent = L"%%";
    static constexpr std::wstring Option = L"⌥";
    static constexpr std::wstring ArrowUp = L"↑";
    static constexpr std::wstring ArrowDown = L"↓";
    static constexpr std::wstring ArrowUpOutline = L"⇧";
    static constexpr std::wstring ArrowLeft = L"←";
    static constexpr std::wstring ArrowRight = L"→";
    static constexpr std::wstring LineHorizDown = L"┬";
    static constexpr std::wstring LineHorizUp = L"┴";
    static constexpr std::wstring LineForwardSlash = L"╱";
    static constexpr std::wstring LineBackSlash = L"╲";
    static constexpr std::wstring LineVertLeft = L"┤";
    static constexpr std::wstring LineVertRight = L"├";
    static constexpr std::wstring TriangleRight = L"⏵";
    static constexpr std::wstring Return = L"⏎";
    static constexpr std::wstring ArrowRightVertLine = L"⇥";
};

}
