//
// Created by James Pickering on 1/22/25.
//

#include "sampler_view.hpp"

#include "../api/audio_file.hpp"
#include "../view/channel_rack_view.hpp"

#include <trundle/trundle.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/widget/label_widget.hpp>
#include <trundle/widget/meter_widget.hpp>
#include <trundle/widget/text_field_widget.hpp>

namespace examples {

SamplerView::SamplerView(Widget* parent) :
    FrameWidget{parent} {
    setTitle(L"Sampler");
    setFrameStyle(FrameStyle::Window);

    const auto controlsLabel = addChild<LabelWidget>();
    controlsLabel->setText(Unicode::TriangleRight + L" Controls:");
    controlsLabel->setHighlighted(true);

    auto volumeLabel = addChild<LabelWidget>();
    volumeLabel->setText(L"\uf027 Gain:");

    auto volumeMeter = addChild<MeterWidget>();
    volumeMeter->setMinValue(-60.0);
    volumeMeter->setMaxValue(6.0);
    volumeMeter->setValue(-6.0);
    volumeMeter->setWidth(10);

    auto panLabel = addChild<LabelWidget>();
    panLabel->setText(Unicode::ArrowLeftRight + L" Pan:");

    const auto panMeter = addChild<MeterWidget>();
    panMeter->setMinValue(-10);
    panMeter->setMaxValue(10);
    panMeter->setValue(-2);
    panMeter->setWidth(10);
    panMeter->setMeterType(MeterType::LeftRight);
    panMeter->setLeftBound(L"L");
    panMeter->setRightBound(L"R");

    const auto waveformLabel = addChild<LabelWidget>();
    waveformLabel->setText(Unicode::TriangleRight + L" Waveform:");
    waveformLabel->setHighlighted(true);

    auto attackLabel = addChild<LabelWidget>();
    attackLabel->setText(Unicode::LineForwardSlash + L" Attack:");

    auto attackMeter = addChild<MeterWidget>();
    attackMeter->setMinValue(-60.0);
    attackMeter->setMaxValue(6.0);
    attackMeter->setValue(-6.0);
    attackMeter->setWidth(10);
    attackMeter->setUseColors(false);

    auto decayLabel = addChild<LabelWidget>();
    decayLabel->setText(Unicode::LineBackSlash + L" Decay:");

    const auto decayMeter = addChild<MeterWidget>();
    decayMeter->setMinValue(-10);
    decayMeter->setMaxValue(10);
    decayMeter->setValue(-2);
    decayMeter->setWidth(10);
    decayMeter->setUseColors(false);

    controlsLabel->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 2},
                                         {LayoutAttr::Top, this, LayoutAttr::Top, static_cast<double>(headerHeight())},
                                         {LayoutAttr::Width, 20},
                                         {LayoutAttr::Height, 1}});

    volumeLabel->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 2},
                                       {LayoutAttr::Top, controlsLabel, LayoutAttr::Bottom, 1},
                                       {LayoutAttr::Width, 10},
                                       {LayoutAttr::Height, 1}});

    volumeMeter->addLayoutConstraints({{LayoutAttr::Left, volumeLabel, LayoutAttr::Right},
                                       {LayoutAttr::Top, volumeLabel, LayoutAttr::Top},
                                       {LayoutAttr::Width, 20},
                                       {LayoutAttr::Height, 2}});

    panLabel->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 2},
                                    {LayoutAttr::Top, volumeLabel, LayoutAttr::Bottom, 2},
                                    {LayoutAttr::Width, 10},
                                    {LayoutAttr::Height, 1}});

    panMeter->addLayoutConstraints({{LayoutAttr::Left, panLabel, LayoutAttr::Right},
                                    {LayoutAttr::Top, panLabel, LayoutAttr::Top},
                                    {LayoutAttr::Width, 10},
                                    {LayoutAttr::Height, 2}});

    attackLabel->addLayoutConstraints({{LayoutAttr::Left, volumeMeter, LayoutAttr::Right, 5},
                                       {LayoutAttr::Top, controlsLabel, LayoutAttr::Bottom, 1},
                                       {LayoutAttr::Width, 10},
                                       {LayoutAttr::Height, 1}});

    attackMeter->addLayoutConstraints({{LayoutAttr::Left, attackLabel, LayoutAttr::Right},
                                       {LayoutAttr::Top, attackLabel, LayoutAttr::Top},
                                       {LayoutAttr::Width, 20},
                                       {LayoutAttr::Height, 2}});

    decayLabel->addLayoutConstraints({{LayoutAttr::Left, attackLabel, LayoutAttr::Left},
                                      {LayoutAttr::Top, attackLabel, LayoutAttr::Bottom, 2},
                                      {LayoutAttr::Width, 10},
                                      {LayoutAttr::Height, 1}});

    decayMeter->addLayoutConstraints({{LayoutAttr::Left, decayLabel, LayoutAttr::Right},
                                      {LayoutAttr::Top, decayLabel, LayoutAttr::Top},
                                      {LayoutAttr::Width, 10},
                                      {LayoutAttr::Height, 2}});

    waveformLabel->addLayoutConstraints({{LayoutAttr::Left, panLabel, LayoutAttr::Left},
                                         {LayoutAttr::Width, 15},
                                         {LayoutAttr::Height, 1},
                                         {LayoutAttr::Bottom, this, LayoutAttr::Bottom, -12}});
}

auto SamplerView::setAudioFile(AudioFile* file) -> void {
    _audioFile = file;
    setTitle(L"Sampler - " + _audioFile->displayName);
    clear();
}

auto SamplerView::render() const -> void {
    FrameWidget::render();

    if (_audioFile == nullptr) {
        return;
    }

    const auto maxSteps = 10;

    auto ampPos = glm::ivec2{pos().x + 2, pos().y + size().y - maxSteps / 2 - 1};

    if (_audioFile->spec.format == SDL_AUDIO_S16LE) {
        auto samples = std::vector<std::int16_t>{};
        auto maxAmp = std::int16_t{};

        const auto width = size().x * 2 - 15;
        auto byteStep = _audioFile->wavDataLen / width;
        if (byteStep % 2 > 0) {
            --byteStep;
        }

        for (auto i = 0; i < width; i += 2) {
            auto sample = std::int16_t{};
            sample |= _audioFile->wavData[i * byteStep];
            sample |= _audioFile->wavData[i * byteStep + 1] << 8;
            samples.push_back(sample);
            maxAmp = std::max(maxAmp, static_cast<std::int16_t>(sample > 0 ? sample : -sample));// TODO: use std::abs
        }

        auto ampIdx = 0;

        auto lastTotalSteps = 0.;

        Trundle::setColorPair(ColorPair::BlueOnDefault);
        for (const auto& amp : samples) {
            const auto normAmp = amp / static_cast<double>(maxAmp);
            const auto totalSteps = normAmp * static_cast<double>(maxSteps);
            const auto rightAligned = static_cast<bool>(ampIdx % 2);

            for (auto step = 0; step < std::abs(totalSteps); ++step) {
                if (totalSteps > 0) {
                    Trundle::moveCursor({ampPos.x, ampPos.y - step / 2 - 1});
                } else {
                    Trundle::moveCursor({ampPos.x, ampPos.y + step / 2});
                }

                const auto isBottomBlock = !static_cast<bool>(step % 2);
                const auto canShareBlocks = rightAligned && (lastTotalSteps > 0 && totalSteps > 0 || lastTotalSteps < 0 && totalSteps < 0);

                if (canShareBlocks && step <= std::abs(lastTotalSteps)) {
                    // TODO: do the corner pieces
                    Trundle::print(Unicode::Block);
                } else if (rightAligned) {
                    if (isBottomBlock) {
                        Trundle::print(totalSteps > 0 ? Unicode::BlockBottomRight : Unicode::BlockTopRight);
                    } else {
                        Trundle::print(Unicode::BlockRight);
                    }
                } else {
                    if (isBottomBlock) {
                        Trundle::print(totalSteps > 0 ? Unicode::BlockBottomLeft : Unicode::BlockTopLeft);
                    } else {
                        Trundle::print(Unicode::BlockLeft);
                    }
                }
            }

            lastTotalSteps = totalSteps;
            ++ampIdx;
            if (rightAligned) {
                ++ampPos.x;
            }
        }
        Trundle::setColorPair(Trundle::defaultColorPair());
    }
}

}