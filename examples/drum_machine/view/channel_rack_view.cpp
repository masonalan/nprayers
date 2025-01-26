//
// Created by James Pickering on 1/22/25.
//

#include "channel_rack_view.hpp"

#include "../api/audio_file.hpp"
#include "../api/pattern.hpp"
#include "../api/project.hpp"
#include "../model/track_list_model.hpp"
#include "../render/track_header_render_delegate.hpp"
#include "../render/track_item_render_delegate.hpp"

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/unicode.hpp>
#include <trundle/view/prompt_view.hpp>
#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/label_widget.hpp>
#include <trundle/widget/list_widget.hpp>
#include <trundle/widget/picker_widget.hpp>

namespace examples {

static auto trackHeaderRenderDelegate = std::make_unique<TrackHeaderRenderDelegate>();
static auto trackItemRenderDelegate = std::make_unique<TrackItemRenderDelegate>();

ChannelRackView::ChannelRackView(Project* project, Widget* parent) :
    FrameWidget{parent},
    _project{project} {
    setTitle(L"Channel Rack");
    setFrameStyle(FrameStyle::Window);

    const auto patternLabel = addChild<LabelWidget>();
    patternLabel->setText(L"\uf001 Pattern:");
    patternLabel->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 2},
                                        {LayoutAttr::Top, this, LayoutAttr::Top, static_cast<double>(headerHeight())},
                                        {LayoutAttr::Width, 12},
                                        {LayoutAttr::Height, 1}});

    const auto patternPicker = addChild<PickerWidget>();
    patternPicker->setOptions({L"Pattern 1", L"Pattern 2", L"Pattern 3"});
    patternPicker->addLayoutConstraints({{LayoutAttr::Left, patternLabel, LayoutAttr::Right},
                                         {LayoutAttr::Top, patternLabel, LayoutAttr::Top},
                                         {LayoutAttr::Width, 20},
                                         {LayoutAttr::Height, 1}});

    const auto barsLabel = addChild<LabelWidget>();
    barsLabel->setText(L"\U000f0758 Bars:");
    barsLabel->addLayoutConstraints({{LayoutAttr::Left, patternPicker, LayoutAttr::Right},
                                     {LayoutAttr::Top, patternPicker, LayoutAttr::Top},
                                     {LayoutAttr::Width, 12},
                                     {LayoutAttr::Height, 1}});

    const auto barsPicker = addChild<PickerWidget>();
    barsPicker->setOptions({L"2", L"4", L"8", L"16"});
    barsPicker->addLayoutConstraints({{LayoutAttr::Left, barsLabel, LayoutAttr::Right},
                                      {LayoutAttr::Top, barsLabel, LayoutAttr::Top},
                                      {LayoutAttr::Width, 20},
                                      {LayoutAttr::Height, 1}});

    _trackListModel = TrackListModel{_project};

    _trackList = addChild<ListWidget>();
    _trackList->setModel(&_trackListModel);
    _trackList->setUpKey(Key::ShiftUp);
    _trackList->setDownKey(Key::ShiftDown);
    _trackList->setHeaderRenderDelegate(trackHeaderRenderDelegate.get());
    _trackList->setItemRenderDelegate(trackItemRenderDelegate.get());
    _trackList->addLayoutConstraints({{LayoutAttr::Left, this, LayoutAttr::Left, 2},
                                      {LayoutAttr::Right, this, LayoutAttr::Right, 2},
                                      {LayoutAttr::Top, patternLabel, LayoutAttr::Bottom, 1},
                                      {LayoutAttr::Bottom, actionBar(), LayoutAttr::Top, -1}});

    addAction(Key::Enter, L"Place Note", [this](auto) {
        const auto file = _project->audioFiles().at(_project->currentPattern()->selectedField().y).get();
        if (!_project->currentPattern()->containsAudioFile(file)) {
            _project->currentPattern()->addAudioFile(file);
        }
        _project->currentPattern()->track(file)[_project->currentPattern()->selectedField().x] = !_project->currentPattern()->track(file)[_project->currentPattern()->selectedField().x];
    });

    addAction(Key::Delete, L"Remove Audio File", [this](auto) {
        const auto file = _project->audioFiles().at(_trackList->selectedRow()).get();

        Prompt::create(window(), L"Remove Audio File", L"Are you sure you want to remove " + file->displayName + L"?", [this](auto) { _project->removeAudioFile(_trackList->selectedRow()); }, [this](auto) {});
    });

    addAction(Key::Space, L"Play/Pause", [this](auto) {
        _project->playing() ? _project->pause() : _project->play();
    });

    actionBar()->displayActions(actions());
}

auto ChannelRackView::setProject(Project* rack) -> void {
    _project = rack;
}

auto ChannelRackView::list() const -> ListWidget* {
    return _trackList;
}

auto ChannelRackView::update() -> void {
    if (focused()) {
        switch (Keyboard::currKey()) {
        case Key::Right: {
            clear();
            auto cursor = _project->currentPattern()->selectedField();
            ++cursor.x;
            _project->currentPattern()->setSelectedField(cursor);
            break;
        }
        case Key::Left: {
            clear();
            auto cursor = _project->currentPattern()->selectedField();
            --cursor.x;
            _project->currentPattern()->setSelectedField(cursor);
            break;
        }
        case Key::Up: {
            clear();
            auto cursor = _project->currentPattern()->selectedField();
            --cursor.y;
            _project->currentPattern()->setSelectedField(cursor);
            break;
        }
        case Key::Down: {
            clear();
            auto cursor = _project->currentPattern()->selectedField();
            ++cursor.y;
            _project->currentPattern()->setSelectedField(cursor);
            break;
        }
        default:
            break;
        }
    }
}

}