// //
// // Created by James Pickering on 1/25/25.
// //
//
// #pragma once
//
// #include <trundle/model/model.hpp>
// #include <trundle/widget/widget.hpp>
//
// namespace trundle {
// struct LabelWidget;
// }
//
// using namespace trundle;
//
// namespace examples {
//
// struct AudioFile;
// struct Pattern;
//
// struct TrackWidget : Widget {
//     explicit TrackWidget(Widget* parent = nullptr);
//
//     auto setPattern(Pattern* pattern) -> void;
//     auto setAudioFile(AudioFile* source) -> void;
//     auto setNumber(int number) -> void;
//
// protected:
//     auto render() const -> void override;
//
// private:
//     LabelWidget* _nameLabel;
//
//     AudioFile* _sourceFile{nullptr};
//     Pattern* _pattern{nullptr};
//
//     int _number{0};
// };
//
// }