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
    _cursor = _text.begin();
}

auto TextFieldWidget::setText(const std::wstring& text) -> void {
    clear();
    _text.setText(text);
    _cursor = _text.begin();
    updateTextLayout();
}

auto TextFieldWidget::setTextChanged(TextChangedCallback&& callback) -> void {
    _textChanged = callback;
}

auto TextFieldWidget::setCursor(WrappingTextIterator cursor) -> void {
    _cursor = cursor;
    updateTextLayout();
}

auto TextFieldWidget::text() const -> const std::wstring& {
    return _text.text();
}

auto TextFieldWidget::update() -> void {
    if (focused()) {
        switch (Keyboard::currKey()) {
        case Key::Left:
            moveCursor(Direction::Left);
            break;
        case Key::Right:
            moveCursor(Direction::Right);
            break;
        case Key::Up:
            moveCursor(Direction::Up);
            break;
        case Key::Down:
            moveCursor(Direction::Down);
            break;
        case Key::Delete:
            if (_cursor != _text.begin()) {
                _cursor = _text.erase(std::prev(_cursor));
                updateTextLayout();
            }
            break;
        case Key::Enter:
            _cursor = _text.insert(_cursor, '\n');
            updateTextLayout();
            moveCursor(Direction::Down);
            break;
        default:
            if (const auto key = Keyboard::currChar(); key >= 32 && key <= 127) {
                _cursor = _text.insert(_cursor, key);
                updateTextLayout();
                moveCursor(Direction::Right);

                if (_textChanged) {
                    _textChanged(this);
                }
            }
            break;
        }
    }
}

auto TextFieldWidget::render() const noexcept -> void {
    const auto p = glm::ivec2{pos().x, pos().y};
    auto linePos = glm::ivec2{0, 0};

    for (const auto& rowStr : _text.rows()) {
        Trundle::moveCursor(p + linePos);
        Trundle::print(rowStr);
        Trundle::print(String::Space);
        ++linePos.y;
    }

    const auto ch = WrappingText::printableChar(*_cursor);

    Trundle::moveCursor(p + _cursorPos);
    Trundle::setColorPair(Trundle::highlightColorPair());
    Trundle::print(std::string{ch == char{} ? ' ' : ch});
    Trundle::setColorPair(Trundle::defaultColorPair());
}

auto TextFieldWidget::willAppear() -> void {
    _text.setBounds({size().x - 1, size().y});
    updateTextLayout();
}

auto TextFieldWidget::updateTextLayout() -> void {
    if (!layoutResolved()) {
        return;
    }

    clear();
    _cursorPos = _text.posAtIterator(_cursor);
}

auto TextFieldWidget::moveCursor(Direction direction) -> void {
    _cursor = _text.iteratorRelativeToIterator(_cursor, direction);
    _cursorPos = _text.posAtIterator(_cursor);

    if (direction == Direction::Left || direction == Direction::Right) {
        _text.setPreferredX(_cursorPos.x);
    }
}

}