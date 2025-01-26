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
    static constexpr std::wstring BlockBottomLeft = L"▖";
    static constexpr std::wstring BlockBottomLeftRight = L"▟";
    static constexpr std::wstring BlockBottomRight = L"▗";
    static constexpr std::wstring BlockLeft = L"▌";
    static constexpr std::wstring BlockRight = L"▐";
    static constexpr std::wstring BlockTop = L"▀";
    static constexpr std::wstring BlockTopLeft = L"▘";
    static constexpr std::wstring BlockTopLeftRight = L"▜";
    static constexpr std::wstring BlockLeftBottomRight = L"▙";
    static constexpr std::wstring BlockLeftTopRight = L"▛";
    static constexpr std::wstring BlockTopRight = L"▝";
    static constexpr std::wstring BlockBottom = L"▄";
    static constexpr std::wstring BlockMediumShade = L"▒";
    static constexpr std::wstring BlockLightShade = L"░";
    static constexpr std::wstring Square = L"■";
    static constexpr std::wstring LineVert = L"│";
    static constexpr std::wstring LineHoriz = L"─";
    static constexpr std::wstring LineHorizDouble = L"═";
    static constexpr std::wstring CircleFilled = L"◉";
    static constexpr std::wstring CornerTopRight = L"┐";
    static constexpr std::wstring CornerTopRightHorizDouble = L"╕";
    static constexpr std::wstring CornerTopRightRounded = L"╮";
    static constexpr std::wstring CornerTopLeft = L"┌";
    static constexpr std::wstring CornerTopLeftHorizDouble = L"╒";
    static constexpr std::wstring CornerTopLeftRounded = L"╭";
    static constexpr std::wstring CornerBottomRight = L"┘";
    static constexpr std::wstring CornerBottomLeft = L"└";
    static constexpr std::wstring Dot = L"•";
    static constexpr std::wstring FolderClosed = L"\uf07b";
    static constexpr std::wstring FolderOpened = L"\uf07c";
    static constexpr std::wstring ArrowRightDouble = L"»";
    static constexpr std::wstring Percent = L"%%";
    static constexpr std::wstring Option = L"⌥";
    static constexpr std::wstring ArrowUp = L"↑";
    static constexpr std::wstring ArrowDown = L"↓";
    static constexpr std::wstring ArrowUpOutline = L"⇧";
    static constexpr std::wstring ArrowLeft = L"←";
    static constexpr std::wstring ArrowRight = L"→";
    static constexpr std::wstring ArrowLeftRight = L"\uf08f";
    static constexpr std::wstring Helmet = L"\ued69";
    static constexpr std::wstring Lines = L"\uef4c";
    static constexpr std::wstring LineHorizDown = L"┬";
    static constexpr std::wstring LineHorizRight = L"╶";
    static constexpr std::wstring LineHorizUp = L"┴";
    static constexpr std::wstring LineForwardSlash = L"╱";
    static constexpr std::wstring LineBackSlash = L"∖"; // ∖
    static constexpr std::wstring LineCenterBottomRight = L"⸜";
    static constexpr std::wstring LineVertLeft = L"┤";
    static constexpr std::wstring LineVertLeftDouble = L"╡";
    static constexpr std::wstring LineVertRight = L"├";
    static constexpr std::wstring LineVertRightDouble = L"╞";
    static constexpr std::wstring MagnifyingGlass = L"\uf002";
    static constexpr std::wstring Midi = L"\U000f08f2";
    static constexpr std::wstring Minimize = L"\ue224";
    static constexpr std::wstring Plus = L"\uf00d";
    static constexpr std::wstring TriangleDown = L"\ueb6e";
    static constexpr std::wstring TriangleLeft = L"\ueb6f";
    static constexpr std::wstring TriangleRight = L"\ueb70";
    static constexpr std::wstring TriangleUp = L"\ueb71";
    static constexpr std::wstring Return = L"⏎";
    static constexpr std::wstring ArrowRightVertLine = L"⇥";
    static constexpr std::wstring Wave = L"\U000f095b";
};

}
