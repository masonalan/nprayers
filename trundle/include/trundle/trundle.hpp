//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <trundle/util/color_pair.hpp>

#include <glm/glm.hpp>

#include <functional>
#include <string>
#include <vector>

namespace trundle {

struct Trundle {
    static auto init() -> void;
    static auto clear() -> void;
    static auto refresh() -> void;
    static auto end() -> void;

    static auto print(const std::wstring& str) -> void;
    //static auto print(std::wstring_view str) -> void;
    static auto print(std::wstring_view str) -> void;
    static auto print(std::wstring_view str, unsigned int maxChars) -> void;
    static auto print(wchar_t ch) -> void;
    static auto print(char32_t ch) -> void;
    static auto moveCursor(glm::ivec2 pos) -> void;
    static auto setColorPair(ColorPair pair) -> void;
    static auto setDefaultColorPair(ColorPair pair) -> void;
    static auto setFocusColorPair(ColorPair pair) -> void;
    static auto setHighlightColorPair(ColorPair pair) -> void;
    static auto setFocusHighlightColorPair(ColorPair pair) -> void;
    static auto log(std::wstring str) -> void;

    static auto setOnLogUpdated(std::function<void()>&& fn) -> void;

    [[nodiscard]] static auto defaultColorPair() -> ColorPair;
    [[nodiscard]] static auto focusColorPair() -> ColorPair;
    [[nodiscard]] static auto highlightColorPair() -> ColorPair;
    [[nodiscard]] static auto focusHighlightColorPair() -> ColorPair;
    [[nodiscard]] static auto windowSize() -> glm::ivec2;
    [[nodiscard]] static auto currChar() -> int;
    [[nodiscard]] static auto log() -> const std::vector<std::wstring>&;
};

}
