//
// Created by James Pickering on 12/26/24.
//

#include <trundle/widget/text_field_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/action.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/unicode.hpp>

#include <string_view>

namespace trundle {

TextFieldWidget::TextFieldWidget(trundle::Widget* parent) :
    Widget{parent} {
    addAction(Key::Left, "Left", [this](auto _) {
        moveCursor({-1, 0});
    });
    addAction(Key::Right, "Right", [this](auto _) {
        moveCursor({1, 0});
    });
    addAction(Key::Up, "Up", [this](auto _) {
        moveCursor({0, -1});
    });
    addAction(Key::Down, "Down", [this](auto _) {
        moveCursor({0, 1});
    });
}

auto TextFieldWidget::setText(const std::string& text) -> void {
    clear();
    _text = text;
    updateTextLayout();
}

auto TextFieldWidget::update() -> void {
    // TODO: this needs to be rethought but this is going very well
    if (focused()) {
        if (Keyboard::currKey() == Key::Delete) {
            _text.erase(std::prev(iteratorAtCursorPosition()));
            updateTextLayout();
            moveCursor({-1, 0});
        } else if (Keyboard::currKey() == Key::Enter) {
            _text.insert(iteratorAtCursorPosition(), '\n');
            updateTextLayout();
            moveCursor({1, 0});
        } else {
            const auto key = Keyboard::currChar();
            if (key >= 32 && key <= 127) {
                _text.insert(iteratorAtCursorPosition(), key);
                updateTextLayout();
                moveCursor({1, 0});
            }
        }
    }
}

auto TextFieldWidget::render() const noexcept -> void {
    auto buffer = std::string{};
    auto p = glm::ivec2{pos().x + 1, pos().y + 1};
    auto s = glm::ivec2{size().x - 2, size().y - 2};

    auto linePos = glm::ivec2{0, 0};

    for (const auto& rowStr : _rows) {
        Trundle::moveCursor(p + linePos);
        Trundle::print(rowStr);
        ++linePos.y;
    }

    const auto ch = charAtCursorPosition();

    Trundle::moveCursor(p + _cursorPos);
    Trundle::setColorPair(Trundle::highlightColorPair());
    Trundle::print(std::string{ch == char{} ? ' ' : ch});
    Trundle::setColorPair(Trundle::defaultColorPair());
}

auto TextFieldWidget::willAppear() -> void {
    updateTextLayout();
}

auto TextFieldWidget::updateTextLayout() -> void {
    if (!layoutResolved()) {
        return;
    }

    clear();
    _rows.clear();

    auto row = 0;
    auto col = 0;
    auto buffer = std::string{};
    auto p = glm::ivec2{pos().x + 1, pos().y + 1};
    auto s = glm::ivec2{size().x - 2, size().y - 2};
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

    nextWord(_text.end());
    newLine();
}

auto TextFieldWidget::moveCursor(glm::ivec2 delta) -> void {
    if (charAtCursorPosition() == char{}) {
        clear();
    }
    const auto newPos = _cursorPos + delta;
    if (newPos.x > static_cast<int>(_rows[newPos.y].length())) {

    } else if (newPos.x < 0) {
        moveCursor({0, -1});
    } else {
        _cursorPos = {std::max(std::min(newPos.x, static_cast<int>(_rows[newPos.y].length()) - 1), 0),
                      std::max(std::min(newPos.y, static_cast<int>(_rows.size()) - 1), 0)};
    }
}

auto TextFieldWidget::charAtCursorPosition() const noexcept -> char {
    if (_rows.size() <= _cursorPos.y) {
        return char{};
    }
    const auto& row = _rows[_cursorPos.y];
    if (row.length() <= _cursorPos.x) {
        return char{};
    }
    return row.at(_cursorPos.x);
}

auto TextFieldWidget::iteratorAtCursorPosition() -> std::string::iterator {
    if (_text.empty()) {
        return _text.end();
    }
    auto idx = 0;
    for (auto row = 0; row < _cursorPos.y; ++row) {
        idx += static_cast<int>(_rows.at(row).length()) + 1;
    }
    idx += _cursorPos.x;
    return _text.begin() + idx;
}

}