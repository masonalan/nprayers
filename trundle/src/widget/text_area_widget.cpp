//
// Created by James Pickering on 12/26/24.
//

#include <trundle/widget/text_area_widget.hpp>

#include <trundle/trundle.hpp>
#include <trundle/util/unicode.hpp>

namespace trundle {

auto TextAreaWidget::setText(const std::string& text) -> void {
    _text = text;
}

auto TextAreaWidget::render() const -> void {
    auto row = 0;
    auto col = 0;
    auto buffer = std::wstring{};
    for (const auto& ch : _text) {
        if (ch == ' ') {
            if (col + buffer.size() >= size().x) {
                col = 0;
                ++row;
            }
            Trundle::moveCursor({pos().x + col, pos().y + row});
            Trundle::print(buffer);
            Trundle::print(String::Space);
            col += static_cast<int>(buffer.size()) + 1;
            buffer.clear();
        } else if (ch == '\n') {
            Trundle::moveCursor({pos().x + col, pos().y + row});
            Trundle::print(buffer);
            buffer.clear();
            ++row;
            col = 0;
        } else {
            buffer.push_back(ch);
        }
    }
    Trundle::moveCursor({pos().x + col, pos().y + row});
    Trundle::print(buffer);
}

}