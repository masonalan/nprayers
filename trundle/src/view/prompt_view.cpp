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
    setTitleBarStyle(TitleBarStyle::DoubleLine);

    _messageLabel = addChild<LabelWidget>();
    _messageLabel->addLayoutConstraint({LayoutAttribute::Left, this, LayoutAttribute::Left, 3});
    _messageLabel->addLayoutConstraint({LayoutAttribute::Right, this, LayoutAttribute::Right, -2});
    _messageLabel->addLayoutConstraint({LayoutAttribute::Top, this, LayoutAttribute::Top, 2});
    _messageLabel->addLayoutConstraint({LayoutAttribute::Height, 1});

    _arrowLabel = addChild<LabelWidget>();
    _arrowLabel->addLayoutConstraint({LayoutAttribute::Left, this, LayoutAttribute::Left, 3});
    _arrowLabel->addLayoutConstraint({LayoutAttribute::Width, 1});
    _arrowLabel->addLayoutConstraint({LayoutAttribute::Top, _messageLabel, LayoutAttribute::Bottom, 1});
    _arrowLabel->addLayoutConstraint({LayoutAttribute::Height, 1});
    _arrowLabel->setText(Unicode::TriangleRight);

    _textField = addChild<TextFieldWidget>();
    _textField->addLayoutConstraint({LayoutAttribute::Left, _arrowLabel, LayoutAttribute::Right, 1});
    _textField->addLayoutConstraint({LayoutAttribute::Right, this, LayoutAttribute::Right, -2});
    _textField->addLayoutConstraint({LayoutAttribute::Top, _arrowLabel, LayoutAttribute::Top});
    _textField->addLayoutConstraint({LayoutAttribute::Height, 1});
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

    _actionBar = addChild<ActionBarWidget>();

    addLayoutConstraint({LayoutAttribute::Width, 40});
    addLayoutConstraint({LayoutAttribute::Height, 9});
    addLayoutConstraint({LayoutAttribute::Left, parent, LayoutAttribute::Left, [](auto w, auto p, auto val) {
                             const auto pWidth = p->layoutAttributeValue(LayoutAttribute::Width).value().result;
                             const auto wWidth = w->layoutAttributeValue(LayoutAttribute::Width).value().result;
                             return pWidth / 2. - wWidth / 2.;
                         }});
    addLayoutConstraint({LayoutAttribute::Top, parent, LayoutAttribute::Top, [](auto w, auto p, auto val) {
                             const auto pHeight = p->layoutAttributeValue(LayoutAttribute::Height).value().result;
                             const auto wHeight = w->layoutAttributeValue(LayoutAttribute::Height).value().result;
                             return pHeight / 2. - wHeight / 2.;
                         }});

    addAction(Key::Escape, "Cancel", [this](auto) {
        if (_onReject) {
            _onReject(this);
        }
        setVisible(false);
        window()->setFocusLocked(false);
    });
    addAction(Key::CtrlK, "Okay", [this](auto) {
        if (_onAccept) {
            _onAccept(this);
        }
        setVisible(false);
        window()->setFocusLocked(false);
    });

    _actionBar->displayActions(actions());
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

auto PromptView::window() -> WindowWidget* {
    return dynamic_cast<WindowWidget*>(parent());
}

auto PromptView::update() -> void {
}

auto PromptView::render() const noexcept -> void {
    clear();
    FrameWidget::render();
}

auto PromptView::focusChanged() -> void {
    window()->setFocusLocked(true);
}

auto Prompt::create(WindowWidget* window,
                    const std::string& title,
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

    window->setFocused(prompt);

    return prompt;
}

auto Prompt::createWithTextField(WindowWidget* window,
                                 const std::string& title,
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