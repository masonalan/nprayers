//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/util/color_pair.hpp>

#include <glm/glm.hpp>

#include <string>

namespace trundle {

struct Trundle {
    static auto init() -> void;
    static auto clear() -> void;
    static auto refresh() -> void;
    static auto end() -> void;

    static auto print(const std::string& str) -> void;
    static auto print(std::string_view str) -> void;
    static auto print(std::wstring_view str) -> void;
    static auto moveCursor(glm::ivec2 pos) -> void;
    static auto setColorPair(ColorPair pair) -> void;
    static auto setDefaultColorPair(ColorPair pair) -> void;
    static auto setFocusColorPair(ColorPair pair) -> void;
    static auto setHighlightColorPair(ColorPair pair) -> void;

    [[nodiscard]] static auto defaultColorPair() -> ColorPair;
    [[nodiscard]] static auto focusColorPair() -> ColorPair;
    [[nodiscard]] static auto highlightColorPair() -> ColorPair;
    [[nodiscard]] static auto windowSize() -> glm::ivec2;
    [[nodiscard]] static auto currChar() -> int;
};

}
