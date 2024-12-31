//
// Created by James Pickering on 12/23/24.
//

#include <trundle/trundle.hpp>

#include <trundle/util/color_pair.hpp>

#include <locale>
#include <ncurses.h>

namespace trundle {

struct TrundleData {
    ColorPair defaultColorPair = ColorPair::Default;
    ColorPair focusColorPair = ColorPair::GreenOnDefault;
    ColorPair highlightColorPair = ColorPair::BlackOnGreen;
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

auto Trundle::print(const std::string& str) -> void {
    printw(str.c_str());
}

auto Trundle::print(std::string_view str) -> void {
    addnstr(str.data(), str.length());
}

auto Trundle::moveCursor(glm::ivec2 pos) -> void {
    move(pos.y, pos.x);
}

auto Trundle::setColorPair(ColorPair pair) -> void {
    attron(COLOR_PAIR(static_cast<std::underlying_type_t<ColorPair>>(pair)));
}

auto Trundle::setDefaultColorPair(trundle::ColorPair pair) -> void {
    _d.defaultColorPair = pair;
}

auto Trundle::setFocusColorPair(trundle::ColorPair pair) -> void {
    _d.focusColorPair = pair;
}

auto Trundle::setHighlightColorPair(trundle::ColorPair pair) -> void {
    _d.highlightColorPair = pair;
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

auto Trundle::currChar() -> int {
    return getch();
}

}