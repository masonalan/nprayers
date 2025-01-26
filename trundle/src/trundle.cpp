//
// Created by James Pickering on 12/23/24.
//

#include <trundle/trundle.hpp>

#include <trundle/util/color_pair.hpp>

#define NCURSES_WIDECHAR 1
#define _XOPEN_SOURCE_EXTENDED//NOLINT
#define _XOPEN_SOURCE 500     //NOLINT

#include <functional>
#include <locale>
#include <ncurses.h>
#include <string>
#include <vector>

namespace trundle {
struct TrundleData {
    ColorPair defaultColorPair = ColorPair::Default;
    ColorPair focusColorPair = ColorPair::GreenOnDefault;
    ColorPair highlightColorPair = ColorPair::BlackOnDefault;
    ColorPair focusHighlightColorPair = ColorPair::BlackOnGreen;

    std::vector<std::wstring> log{};

    std::function<void()> onLogUpdated;
};

static auto _d = TrundleData{};

static auto initColorPair(ColorPair pair, short foreground, short background) -> void {
    init_pair(static_cast<std::underlying_type_t<ColorPair>>(pair), foreground, background);
}

auto Trundle::init() -> void {
    setlocale(LC_ALL, "");
    initscr();
    use_default_colors();
    start_color();
    curs_set(0);

    initColorPair(ColorPair::Default, -1, -1);
    initColorPair(ColorPair::BlackOnGreen, COLOR_BLACK, COLOR_GREEN);
    initColorPair(ColorPair::YellowOnDefault, COLOR_YELLOW, -1);
    initColorPair(ColorPair::BlackOnYellow, COLOR_BLACK, COLOR_YELLOW);
    initColorPair(ColorPair::GreenOnDefault, COLOR_GREEN, -1);
    initColorPair(ColorPair::RedOnDefault, COLOR_RED, -1);
    initColorPair(ColorPair::MagentaOnGreen, COLOR_GREEN, COLOR_MAGENTA);
    initColorPair(ColorPair::MagentaOnYellow, COLOR_YELLOW, COLOR_MAGENTA);
    initColorPair(ColorPair::MagentaOnRed, COLOR_RED, COLOR_MAGENTA);
    initColorPair(ColorPair::BlueOnGreen, COLOR_GREEN, COLOR_BLUE);
    initColorPair(ColorPair::BlueOnYellow, COLOR_YELLOW, COLOR_BLUE);
    initColorPair(ColorPair::BlueOnRed, COLOR_RED, COLOR_BLUE);
    initColorPair(ColorPair::WhiteOnYellow, COLOR_BLACK, COLOR_YELLOW);
    initColorPair(ColorPair::DefaultOnRed, -1, COLOR_RED);
    initColorPair(ColorPair::BlueOnDefault, COLOR_BLUE, -1);
    initColorPair(ColorPair::DefaultOnBlue, COLOR_WHITE, COLOR_BLUE);
    initColorPair(ColorPair::BlackOnDefault, COLOR_BLACK, COLOR_WHITE);
    initColorPair(ColorPair::RedOnYellow, COLOR_RED, COLOR_YELLOW);
    initColorPair(ColorPair::YellowOnWhite, COLOR_YELLOW, COLOR_WHITE);

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
}

auto Trundle::clear() -> void {
    ::clear();
}

auto Trundle::refresh() -> void {
    ::refresh();
}

auto Trundle::end() -> void {
    endwin();
}

auto Trundle::print(const std::wstring& str) -> void {
    addnwstr(str.data(), str.length());
}

auto Trundle::print(std::wstring_view str) -> void {
    addnwstr(str.data(), str.length());
}

auto Trundle::print(std::wstring_view str, unsigned int maxChars) -> void {
    if (str.length() > maxChars) {
        addnwstr(str.data(), maxChars - 3);
        printw("...");
    } else {
        Trundle::print(str);
    }
}

auto Trundle::print(wchar_t ch) -> void {
    addnwstr(&ch, 1);
}

auto Trundle::print(char32_t ch) -> void {
    auto cc = cchar_t{};
    const auto c = static_cast<wchar_t>(ch);
    attr_t attrs = A_BOLD | A_UNDERLINE;
    short color_pair = 1;
    setcchar(&cc, &c, attrs, color_pair, nullptr);

    add_wch(&cc);
}

auto Trundle::moveCursor(glm::ivec2 pos) -> void {
    move(pos.y, pos.x);
}

auto Trundle::setColorPair(ColorPair pair) -> void {
    attron(COLOR_PAIR(static_cast<std::underlying_type_t<ColorPair>>(pair)));
}

auto Trundle::setDefaultColorPair(ColorPair pair) -> void {
    _d.defaultColorPair = pair;
}

auto Trundle::setFocusColorPair(ColorPair pair) -> void {
    _d.focusColorPair = pair;
}

auto Trundle::setHighlightColorPair(ColorPair pair) -> void {
    _d.highlightColorPair = pair;
}

auto Trundle::setFocusHighlightColorPair(ColorPair pair) -> void {
    _d.focusHighlightColorPair = pair;
}

auto Trundle::defaultColorPair() -> ColorPair {
    return _d.defaultColorPair;
}

auto Trundle::focusColorPair() -> ColorPair {
    return _d.focusColorPair;
}

auto Trundle::highlightColorPair() -> ColorPair {
    return _d.highlightColorPair;
}

auto Trundle::focusHighlightColorPair() -> ColorPair {
    return _d.focusHighlightColorPair;
}

auto Trundle::windowSize() -> glm::ivec2 {
    auto x = int{}, y = int{};
    getmaxyx(stdscr, y, x);
    return glm::ivec2{x, y};
}

auto Trundle::currChar() -> int {
    return getch();
}

auto Trundle::log(std::wstring str) -> void {
    _d.log.push_back(std::move(str));
    if (_d.onLogUpdated) {
        _d.onLogUpdated();
    }
}

auto Trundle::log() -> const std::vector<std::wstring>& {
    return _d.log;
}

auto Trundle::setOnLogUpdated(std::function<void()>&& fn) -> void {
    _d.onLogUpdated = fn;
}

}
