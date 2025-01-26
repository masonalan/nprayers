//
// Created by James Pickering on 1/22/25.
//

#pragma once

#include "../model/track_list_model.hpp"

#include <trundle/widget/frame_widget.hpp>

#include <chrono>

using namespace trundle;

namespace trundle {
struct ListWidget;
}

namespace examples {

struct Pattern;
struct Project;

struct ChannelRackView : FrameWidget {
    explicit ChannelRackView(Project* project, Widget* parent = nullptr);

    auto setProject(Project* rack) -> void;

    [[nodiscard]] auto list() const -> ListWidget*;

protected:
    auto update() -> void override;

private:
    Project* _project{nullptr};

    ListWidget* _trackList{nullptr};
    TrackListModel _trackListModel{nullptr};
};

}
