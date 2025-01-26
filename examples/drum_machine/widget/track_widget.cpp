// //
// // Created by James Pickering on 1/25/25.
// //
//
// #include "../widget/track_widget.hpp"
// #include "../api/audio_file.hpp"
// #include "../api/pattern.hpp"
// #include "../api/project.hpp"
// #include "../view/channel_rack_view.hpp"
//
// #include <trundle/trundle.hpp>
// #include <trundle/util/unicode.hpp>
// #include <trundle/widget/label_widget.hpp>
// #include <trundle/widget/list_widget.hpp>
//
// namespace examples {
//
// auto TrackWidgetIndexRenderDelegate::render(const Widget* widget, Index index, glm::ivec2 pos, bool selected, void* options) const -> void {
//
// }
//
// auto TrackWidgetIndexRenderDelegate::renderHeader(const Widget* widget, glm::ivec2 pos) const -> int {
//
// }
//
// TrackWidget::TrackWidget(Widget* parent) :
//     Widget{parent} {
//     _nameLabel = addChild<LabelWidget>();
//     _nameLabel->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left},
//                                       {LayoutAttr::Width, 30},
//                                       {LayoutAttr::Top, this, LayoutAttr::Top},
//                                       {LayoutAttr::Height, 1}});
//
//     addLayoutConstraints({{LayoutAttr::Left, parent, LayoutAttr::Left},
//                           {LayoutAttr::Right, parent, LayoutAttr::Right},
//                           {LayoutAttr::Height, 3}});
// }
//
// auto TrackWidget::setPattern(Pattern* pattern) -> void {
//     _pattern = pattern;
// }
//
// auto TrackWidget::setAudioFile(AudioFile* source) -> void {
//     _sourceFile = source;
//     _nameLabel->setText(std::to_wstring(_number) + L". " + _sourceFile->displayName);
// }
//
// auto TrackWidget::setNumber(int number) -> void {
//     _number = number;
//     _nameLabel->setText(std::to_wstring(_number) + L". " + _sourceFile->displayName);
// }
//
// auto TrackWidget::render() const -> void {
//     Widget::render();
// }
// }
