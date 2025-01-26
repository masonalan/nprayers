//
// Created by James Pickering on 1/22/25.
//

#include "drum_machine.hpp"

#include "api/audio_file.hpp"
#include "api/pattern.hpp"
#include "api/project.hpp"
#include "api/settings.hpp"
#include "api/util.hpp"
#include "model/file_browser_model.hpp"
#include "view/channel_rack_view.hpp"
#include "view/file_browser_view.hpp"
#include "view/sampler_view.hpp"

#include <trundle/model/filter_model.hpp>
#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/view/tree_view.hpp>
#include <trundle/widget/list_widget.hpp>
#include <trundle/widget/tree_widget.hpp>
#include <trundle/widget/window_widget.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>

#include <filesystem>
#include <string>
#include <vector>

using namespace trundle;

namespace examples {

struct Data {
    Project rack{};
};

static Uint8* wav_data = NULL;
static Uint32 wav_data_len = 0;

auto DrumMachine::run() -> void {
    auto spec = SDL_AudioSpec{};

    if (!SDL_Init(SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }

    /**
     * Setup Settings
     */
    auto settings = Settings{};
    settings.setBrowserPath("/Users/jamespickering/Documents/music/kits");

    /**
     * Setup Project
     */
    auto project = Project{};
    project.setName(L"tromsø");

    const auto pattern = project.pattern(0);
    pattern->setSteps(32);
    pattern->setName(L"drums");

    /**
     * Setup models
     */
    const auto& path = settings.browserPath();
    const auto root = std::make_unique<FileNode>(Util::pathToWideString(path.filename()), path);
    auto model = FileBrowserModel{root.get()};

    auto filterModel = FilterModel{};
    filterModel.setSourceModel(&model);

    /**
     * Setup ui
     */
    auto screen = ScreenWidget{};
    screen.setTitle(L"Drum Machine - " + project.name());

    const auto browser = screen.addChild<FileBrowserView>();
    browser->setTitle(L"Browser");
    browser->tree()->setModel(&filterModel);

    const auto channelRack = screen.addChild<ChannelRackView>(&project);

    const auto sampler = screen.addChild<SamplerView>();

    browser->addLayoutConstraints({{LayoutAttr::Left, &screen, LayoutAttr::Left, 3},
                                   {LayoutAttr::Top, &screen, LayoutAttr::Top, 3},
                                   {LayoutAttr::Width, 40},
                                   {LayoutAttr::Height, &screen, LayoutAttr::Height, -5}});

    channelRack->addLayoutConstraints({{LayoutAttr::Left, browser, LayoutAttr::Right, 3},
                                       {LayoutAttr::Top, &screen, LayoutAttr::Top, 3},
                                       {LayoutAttr::Width, &screen, LayoutAttr::Width, 0, 0.6},
                                       {LayoutAttr::Height, 20}});

    sampler->addLayoutConstraints({{LayoutAttr::Left, channelRack, LayoutAttr::Left},
                                   {LayoutAttr::Top, channelRack, LayoutAttr::Bottom, 2},
                                   {LayoutAttr::Right, &screen, LayoutAttr::Right, -2},
                                   {LayoutAttr::Bottom, browser, LayoutAttr::Bottom}});

    browser->setOnSelectionOpened([&browser, &project, &spec, &sampler]() {
        const auto node = static_cast<FileNode*>(browser->tree()->selectedIndex().data);
        project.addAudioFile(std::make_unique<AudioFile>(node->path, node->name));
        sampler->setAudioFile(project.audioFiles().back().get());
    });

    auto stream = static_cast<SDL_AudioStream*>(nullptr);

    browser->tree()->setOnSelectionChanged([&browser, &spec, &stream](auto) {
        const auto node = static_cast<FileNode*>(browser->tree()->selectedIndex().data);
        if (node->path.extension() == ".wav") {
            if (!SDL_LoadWAV(node->path.c_str(), &spec, &wav_data, &wav_data_len)) {
                SDL_Log("Couldn't load .wav file: %s", SDL_GetError());
                return;
            }

            stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
            if (!stream) {
                SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
                return;
            }

            /* SDL_OpenAudioDeviceStream starts the device paused. You have to tell it to start! */
            SDL_ResumeAudioStreamDevice(stream);
            SDL_PutAudioStreamData(stream, wav_data, wav_data_len);
        }
    });

    channelRack->list()->setOnSelectionChanged([&sampler, &project](auto, auto, auto row) {
        sampler->setAudioFile(project.audioFile(row));
    });

    while (true) {
        project.tick();

        Keyboard::poll();
        screen.performUpdate();
        screen.performRender();
        Trundle::refresh();
    }
}
}