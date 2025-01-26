cmake_minimum_required(VERSION 3.27)
project(trundle-examples)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(trundle)

find_package(SDL3 CONFIG REQUIRED)

add_executable(trundle-examples main.cpp
        examples/text_editor/simple_text_editor.cpp
        examples/text_editor/simple_text_editor.hpp
        examples/text_editor/player_list_model.cpp
        examples/text_editor/player_list_model.hpp
        examples/text_editor/player.cpp
        examples/text_editor/player.hpp
        examples/file_browser/file_browser.hpp
        examples/file_browser/file_browser.cpp
        examples/drum_machine/drum_machine.cpp
        examples/drum_machine/drum_machine.hpp
        examples/drum_machine/model/file_browser_model.hpp
        examples/drum_machine/model/file_browser_model.cpp
        examples/drum_machine/view/file_browser_view.cpp
        examples/drum_machine/view/file_browser_view.hpp
        examples/drum_machine/view/channel_rack_view.cpp
        examples/drum_machine/view/channel_rack_view.hpp
        examples/drum_machine/view/sampler_view.cpp
        examples/drum_machine/view/sampler_view.hpp
        examples/drum_machine/widget/track_widget.hpp
        examples/drum_machine/widget/track_widget.cpp
        examples/drum_machine/api/project.cpp
        examples/drum_machine/api/project.hpp
        examples/drum_machine/api/audio_file.cpp
        examples/drum_machine/api/audio_file.hpp
        examples/drum_machine/api/pattern.cpp
        examples/drum_machine/api/pattern.hpp
        examples/drum_machine/api/settings.cpp
        examples/drum_machine/api/settings.hpp
        examples/drum_machine/api/util.cpp
        examples/drum_machine/api/util.hpp
        examples/drum_machine/model/track_list_model.cpp
        examples/drum_machine/model/track_list_model.hpp
        examples/drum_machine/render/track_item_render_delegate.cpp
        examples/drum_machine/render/track_item_render_delegate.hpp
        examples/drum_machine/render/track_header_render_delegate.cpp
        examples/drum_machine/render/track_header_render_delegate.hpp)

target_link_libraries(trundle-examples trundle)
target_link_libraries(trundle-examples SDL3::SDL3)