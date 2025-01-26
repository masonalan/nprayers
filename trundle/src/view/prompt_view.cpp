//
// Created by James Pickering on 1/1/25.
//

#include <trundle/view/prompt_view.hpp>

#include <trundle/util/action.hpp>
#include <trundle/util/key.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/frame_widget.hpp>
#include <trundle/widget/label_widget.hpp>
#include <trundle/widget/text_field_widget.hpp>
#include <trundle/widget/window_widget.hpp>

namespace trundle {

PromptView::PromptView(Widget* parent) :
    FrameWidget{parent} {
    setFrameStyle(FrameStyle::Window);
    setFrameType(FrameType::Dialog);

    _messageLabel = addChild<LabelWidget>();
    _messageLabel->addLayoutConstraint({LayoutAttr::Left, this, LayoutAttr::Left, 3});
    _messageLabel->addLayoutConstraint({LayoutAttr::Right, this, LayoutAttr::Right, -2});
    _messageLabel->addLayoutConstraint({LayoutAttr::Top, this, LayoutAttr::Top, headerHeight() + 1.0});
    _messageLabel->addLayoutConstraint({LayoutAttr::Height, 1});

    _arrowLabel = addChild<LabelWidget>();
    _arrowLabel->addLayoutConstraint({LayoutAttr::Left, this, LayoutAttr::Left, 3});
    _arrowLabel->addLayoutConstraint({LayoutAttr::Width, 1});
    _arrowLabel->addLayoutConstraint({LayoutAttr::Top, _messageLabel, LayoutAttr::Bottom, 1});
    _arrowLabel->addLayoutConstraint({LayoutAttr::Height, 1});
    _arrowLabel->setText(Unicode::TriangleRight);

    _textField = addChild<TextFieldWidget>();
    _textField->addLayoutConstraint({LayoutAttr::Left, _arrowLabel, LayoutAttr::Right, 1});
    _textField->addLayoutConstraint({LayoutAttr::Right, this, LayoutAttr::Right, -2});
    _textField->addLayoutConstraint({LayoutAttr::Top, _arrowLabel, LayoutAttr::Top});
    _textField->addLayoutConstraint({LayoutAttr::Height, 1});
    _textField->setTextChanged([this](auto) {
        if (_placeholder.empty()) {
            return;
        }

        auto text = _textField->text();
        text.erase(text.find(_placeholder), _placeholder.size());
        _textField->setText(text);
        _textField->setCursor(_textField->text().end());
        _placeholder = std::wstring{};
    });

    addLayoutConstraint({LayoutAttr::Width, 40});
    addLayoutConstraint({LayoutAttr::Height, 11});
    addLayoutConstraint({LayoutAttr::Left, parent, LayoutAttr::Left, [](auto w, auto p, auto val) {
                             const auto pWidth = p->layoutAttributeValue(LayoutAttr::Width).value().result;
                             const auto wWidth = w->layoutAttributeValue(LayoutAttr::Width).value().result;
                             return pWidth / 2. - wWidth / 2.;
                         }});
    addLayoutConstraint({LayoutAttr::Top, parent, LayoutAttr::Top, [](auto w, auto p, auto val) {
                             const auto pHeight = p->layoutAttributeValue(LayoutAttr::Height).value().result;
                             const auto wHeight = w->layoutAttributeValue(LayoutAttr::Height).value().result;
                             return pHeight / 2. - wHeight / 2.;
                         }});

    addAction(Key::Escape, L"Cancel", [this](auto) {
        if (_onReject) {
            _onReject(this);
        }
        setVisible(false);
    });
    addAction(Key::CtrlK, L"Okay", [this](auto) {
        if (_onAccept) {
            _onAccept(this);
        }
        setVisible(false);
    });

    actionBar()->displayActions(actions());
    recalculateLayout();
}

auto PromptView::setMessage(const std::wstring& message) -> void {
    _message = message;
    _messageLabel->setText(_message);
}

auto PromptView::setValue(const std::wstring& value) const -> void {
    _textField->setText(value);
}

auto PromptView::setPlaceholder(const std::wstring& placeholder) -> void {
    _placeholder = placeholder;
    _textField->setText(_placeholder);
}

auto PromptView::setOnAccept(PromptCallback&& callback) -> void {
    _onAccept = callback;
}

auto PromptView::setOnReject(PromptCallback&& callback) -> void {
    _onReject = callback;
}

auto PromptView::setTextFieldVisible(bool visible) const -> void {
    _textField->setVisible(visible);
    _arrowLabel->setVisible(visible);
}

auto PromptView::message() const -> const std::wstring& {
    return _message;
}

auto PromptView::value() const -> const std::wstring& {
    return _textField->text();
}

auto PromptView::window() -> ScreenWidget* {
    return dynamic_cast<ScreenWidget*>(parent());
}

auto PromptView::update() -> void {
}

auto PromptView::render() const -> void {
    clear();
    FrameWidget::render();
}

auto PromptView::focusChanged() -> void {
}

auto Prompt::create(ScreenWidget* window,
                    const std::wstring& title,
                    const std::wstring& message,
                    PromptCallback&& onAccept,
                    PromptCallback&& onReject) -> PromptView* {
    const auto prompt = window->addChild<PromptView>();
    prompt->setTitle(title);
    prompt->setMessage(message);
    prompt->setOnAccept(std::move(onAccept));
    prompt->setOnReject(std::move(onReject));
    prompt->setVisible(true);
    prompt->setTextFieldVisible(false);

    return prompt;
}

auto Prompt::createWithTextField(ScreenWidget* window,
                                 const std::wstring& title,
                                 const std::wstring& message,
                                 const std::wstring& placeholder,
                                 PromptCallback&& onAccept,
                                 PromptCallback&& onReject) -> PromptView* {
    const auto prompt = create(window,
                               title,
                               message,
                               std::move(onAccept),
                               std::move(onReject));

    prompt->setPlaceholder(placeholder);
    prompt->setTextFieldVisible(true);

    return prompt;
}

}