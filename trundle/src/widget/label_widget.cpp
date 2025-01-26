//
// Created by James Pickering on 1/2/25.
//

#include <trundle/widget/label_widget.hpp>

#include <trundle/trundle.hpp>

namespace trundle {

auto LabelWidget::setText(const std::wstring& text) -> void {
    _wrapper.setText(text);
}

auto LabelWidget::setHighlighted(bool highlighted) -> void {
    _highlighted = highlighted;
}

auto LabelWidget::text() const -> const std::wstring& {
    return _wrapper.text();
}

auto LabelWidget::willAppear() -> void {
    _wrapper.setBounds(size());
}

auto LabelWidget::render() const -> void {
    Trundle::setColorPair(Trundle::defaultColorPair());
    auto col = 0;
    for (const auto& row : _wrapper.rows()) {
        Trundle::moveCursor({pos().x, pos().y + col++});
        if (_highlighted) {
            Trundle::setColorPair(ColorPair::WhiteOnYellow);
        }
        Trundle::print(row);
        if (_highlighted) {
            Trundle::setColorPair(Trundle::defaultColorPair());
        }
    }
}

}