//
// Created by James Pickering on 1/2/25.
//

#pragma once

#include <glm/vec2.hpp>

#include <string>
#include <string_view>
#include <vector>

namespace trundle {

enum class Direction {
    Left,
    Right,
    Up,
    Down
};

using WrappingTextIterator = std::wstring::const_iterator;

struct WrappingText {
    auto setText(const std::wstring& text) -> void;
    auto setBounds(glm::ivec2 bounds) -> void;
    auto setPreferredX(int x) -> void;

    auto erase(WrappingTextIterator itr) -> WrappingTextIterator;
    auto insert(WrappingTextIterator itr, char ch) -> WrappingTextIterator;

    [[nodiscard]] auto text() const -> const std::wstring&;
    [[nodiscard]] auto rows() const -> const std::vector<std::wstring_view>&;
    [[nodiscard]] auto begin() const -> WrappingTextIterator;
    [[nodiscard]] auto end() const -> WrappingTextIterator;
    [[nodiscard]] auto iteratorRelativeToIterator(WrappingTextIterator itr, Direction direction) const -> WrappingTextIterator;
    [[nodiscard]] auto iteratorAtPos(glm::ivec2 pos) const -> WrappingTextIterator;
    [[nodiscard]] auto posAtIterator(WrappingTextIterator itr) const -> glm::ivec2;

    [[nodiscard]] static auto printableChar(char ch) -> char;

private:
    auto recalculateRows() -> void;

    std::vector<std::wstring_view> _rows;
    std::wstring _text;
    glm::ivec2 _bounds{};
    int _preferredX{0};
};

}
