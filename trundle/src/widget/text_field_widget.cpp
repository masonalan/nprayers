
#include <trundle/widget/text_field_widget.hpp>

#include <trundle/widget/scroll_bar_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/action.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/unicode.hpp>

#include <string_view>

namespace trundle {
TextFieldWidget::TextFieldWidget(trundle::Widget* parent) :
    Widget{parent} {
    _cursor = _text.begin();

    _scrollBar = addChild<ScrollBarWidget>();
    _scrollBar->addLayoutConstraints({{LayoutAttr::Right, this, LayoutAttr::Right},
                                      {LayoutAttr::Top, this, LayoutAttr::Top},
                                      {LayoutAttr::Bottom, this, LayoutAttr::Bottom}});

    addAction(Key::ShiftLeft, L"Scroll Up", [this](auto) {
        --_scrollOffset;
        _scrollBar->setScrollOffset(_scrollOffset);
        clear();
    });
    addAction(Key::ShiftRight, L"Scroll Down", [this](auto) {
        ++_scrollOffset;
        _scrollBar->setScrollOffset(_scrollOffset);
        clear();
    });
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

auto TextFieldWidget::wrappedText() -> WrappingText& {
    return _text;
}

auto TextFieldWidget::update() -> void {
    if (focused() && visible()) {
        switch (Keyboard::currKey()) {
        case Key::Left:
            moveCursor(Direction::Left);
            break;
        case Key::Right:
            moveCursor(Direction::Right);
            break;
        case Key::Up:
            moveCursor(Direction::Up);

            if (_cursorPos.y < 0 + _scrollOffset) {
                --_scrollOffset;
                _scrollBar->setScrollOffset(_scrollOffset);
                clear();
            }
            break;
        case Key::Down:
            moveCursor(Direction::Down);

            if (_cursorPos.y >= size().y + _scrollOffset) {
                ++_scrollOffset;
                _scrollBar->setScrollOffset(_scrollOffset);
                clear();
            }
            break;
        case Key::Delete:
            if (_cursor != _text.begin()) {
                _cursor = _text.erase(std::prev(_cursor));
                updateTextLayout();

                if (_textChanged) {
                    _textChanged(this);
                }
            }
            break;
        case Key::Enter:
            _cursor = _text.insert(_cursor, '\n');
            updateTextLayout();
            moveCursor(Direction::Down);

            if (_textChanged) {
                _textChanged(this);
            }
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

auto TextFieldWidget::render() const -> void {
    const auto p = glm::ivec2{pos().x, pos().y};
    auto linePos = glm::ivec2{0, 0};

    const auto maxRows = size().y;
    for (auto i = _scrollOffset; i < std::min(maxRows + _scrollOffset, static_cast<int>(_text.rows().size())); ++i) {
        const auto& rowStr = _text.rows().at(i);
        Trundle::moveCursor(p + linePos);
        Trundle::print(rowStr);
        Trundle::print(String::Space);
        ++linePos.y;

        if (i + 1 == maxRows + _scrollOffset) {
            break;
        }
    }

    const auto ch = WrappingText::printableChar(*_cursor);

    if (focused()) {
        auto offset = glm::ivec2{_cursorPos.x, _cursorPos.y - _scrollOffset};
        Trundle::moveCursor(p + offset);
        Trundle::setColorPair(Trundle::focusHighlightColorPair());
        Trundle::print(std::wstring{ch == char{} ? ' ' : ch});
        Trundle::setColorPair(Trundle::defaultColorPair());
    }
}

auto TextFieldWidget::willAppear() -> void {
    _text.setBounds({size().x - 2, size().y});
    updateTextLayout();
}

auto TextFieldWidget::updateTextLayout() -> void {
    if (!layoutResolved()) {
        return;
    }

    clear();
    _cursorPos = _text.posAtIterator(_cursor);
    _scrollBar->setContentHeight(_text.rows().size());
}

auto TextFieldWidget::moveCursor(Direction direction) -> void {
    _cursor = _text.iteratorRelativeToIterator(_cursor, direction);
    _cursorPos = _text.posAtIterator(_cursor);

    if (direction == Direction::Left || direction == Direction::Right) {
        _text.setPreferredX(_cursorPos.x);
    }
}

auto TextFieldWidget::scrollToEnd() -> void {
    _scrollOffset = _text.rows().size() - size().y;
}

}
