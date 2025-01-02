//
// Created by James Pickering on 1/2/25.
//

#include <trundle/widget/label_widget.hpp>

#include <trundle/trundle.hpp>

namespace trundle {

auto LabelWidget::setText(const std::wstring& text) -> void {
    _wrapper.setText(text);
}

auto LabelWidget::text() const -> const std::wstring& {
    return _wrapper.text();
}

auto LabelWidget::willAppear() -> void {
    _wrapper.setBounds(size());
}

auto LabelWidget::render() const noexcept -> void {
    auto col = 0;
    for (const auto& row : _wrapper.rows()) {
        Trundle::moveCursor({pos().x, pos().y + col++});
        Trundle::print(row);
    }
}

}