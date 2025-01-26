//
// Created by James Pickering on 1/22/25.
//

#pragma once

#include <trundle/widget/frame_widget.hpp>

using namespace trundle;

namespace examples {

struct AudioFile;

struct SamplerView : FrameWidget {
    explicit SamplerView(Widget* parent = nullptr);

    auto setAudioFile(AudioFile* file) -> void;

protected:
    auto render() const -> void override;

private:
    AudioFile* _audioFile{nullptr};
};

}
