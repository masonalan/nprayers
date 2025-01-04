cmake_minimum_required(VERSION 3.27)
project(trundle-examples)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(trundle)

add_executable(trundle-examples main.cpp
        examples/text_editor/simple_text_editor.cpp
        examples/text_editor/simple_text_editor.hpp
        examples/text_editor/player_list_model.cpp
        examples/text_editor/player_list_model.hpp
        examples/text_editor/player.cpp
        examples/text_editor/player.hpp
        examples/file_browser/file_browser.hpp
        examples/file_browser/file_browser.cpp)

target_link_libraries(trundle-examples trundle)