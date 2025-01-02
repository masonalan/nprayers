//
// Created by James Pickering on 1/2/25.
//

#include <trundle/util/text.hpp>

namespace trundle {

auto WrappingText::setText(const std::wstring& text) -> void {
    _text = text;
    recalculateRows();
}

auto WrappingText::setBounds(glm::ivec2 bounds) -> void {
    _bounds = bounds;
    recalculateRows();
}

auto WrappingText::setPreferredX(int x) -> void {
    _preferredX = x;
}

auto WrappingText::recalculateRows() -> void {
    _rows.clear();

    auto row = 0;
    auto col = 0;
    auto buffer = std::string{};
    const auto s = glm::ivec2{_bounds.x, _bounds.y};
    auto numChars = 0;
    auto begin = _text.begin();
    auto lastSpace = _text.begin();

    auto nextWord = [&lastSpace, &numChars](auto it) {
        lastSpace = it;
        numChars = 0;
    };

    auto newLine = [this, &begin, &lastSpace, &col, &row]() {
        _rows.emplace_back(begin, lastSpace);
        begin = std::next(lastSpace);
        col = 0;
        ++row;
    };

    for (auto it = _text.begin(); it != _text.end(); ++it) {
        const auto ch = *it;
        if (ch == ' ') {
            if (col + numChars > s.x) {
                newLine();
            }
            col += numChars;
            if (col < s.x) {
                ++col;
            }
            nextWord(it);
        } else if (ch == '\n') {
            nextWord(it);
            newLine();
        } else {
            ++numChars;
            if (numChars > s.x) {
                nextWord(it);
                newLine();
            }
        }
    }

    if (col + numChars > s.x) {
        newLine();
    }
    col += numChars;
    if (col < s.x) {
        ++col;
    }
    nextWord(_text.end());
    newLine();
}

auto WrappingText::erase(WrappingTextIterator itr) -> WrappingTextIterator {
    const auto& newItr = _text.erase(itr);
    recalculateRows();
    return newItr;
}

auto WrappingText::insert(WrappingTextIterator itr, const char ch) -> WrappingTextIterator {
    const auto& newItr = _text.insert(itr, ch);
    recalculateRows();
    return newItr;
}

auto WrappingText::text() const -> const std::wstring& {
    return _text;
}

auto WrappingText::rows() const -> const std::vector<std::wstring_view>& {
    return _rows;
}

auto WrappingText::begin() const -> WrappingTextIterator {
    return _text.cbegin();
}

auto WrappingText::end() const -> WrappingTextIterator {
    return _text.cend();
}

auto WrappingText::iteratorRelativeToIterator(WrappingTextIterator itr, const Direction direction) const -> WrappingTextIterator {
    switch (direction) {
    case Direction::Left:
        if (itr != _text.begin()) {
            return std::prev(itr);
        }
        break;
    case Direction::Right:
        if (itr != _text.end()) {
            return std::next(itr);
        }
        break;
    case Direction::Up: {
        auto pos = posAtIterator(itr);
        --pos.y;
        pos.x = std::max(pos.x, _preferredX);
        return iteratorAtPos(pos);
    }
    case Direction::Down: {
        auto pos = posAtIterator(itr);
        ++pos.y;
        pos.x = std::max(pos.x, _preferredX);
        return iteratorAtPos(pos);
    }
    }

    return itr;
}

auto WrappingText::iteratorAtPos(const glm::ivec2 pos) const -> WrappingTextIterator {
    if (pos.y < 0) {
        return _text.cbegin();
    }
    if (pos.y >= _rows.size()) {
        return _text.cend();
    }

    auto numChars = 0;
    for (auto i = 0; i < pos.y; ++i) {
        numChars += static_cast<int>(_rows.at(i).length()) + 1;
    }
    numChars += std::min(static_cast<int>(_rows.at(pos.y).length()), pos.x);

    if (numChars > _text.length()) {
        return _text.cend();
    }

    return _text.cbegin() + numChars;
}

auto WrappingText::posAtIterator(WrappingTextIterator itr) const -> glm::ivec2 {
    const auto distance = std::distance(_text.cbegin(), itr);

    auto numChars = 0;
    for (auto i = 0; i < _rows.size(); ++i) {
        const auto rowLength = static_cast<int>(_rows.at(i).length()) + 1;
        if (numChars + rowLength > distance) {
            return {distance - numChars, i};
        }
        numChars += rowLength;
    }

    throw std::runtime_error("Cursor position out of range");
}

auto WrappingText::printableChar(const char ch) -> char {
    switch (ch) {
    case '\n':
        return ' ';
    default:
        return ch;
    }
}

}