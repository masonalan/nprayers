cmake_minimum_required(VERSION 3.27)
project(trundle-examples)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(trundle)

add_executable(trundle-examples main.cpp
        examples/simple-text-editor/simple_text_editor.cpp
        examples/simple-text-editor/simple_text_editor.hpp
        examples/simple-text-editor/player_list_model.cpp
        examples/simple-text-editor/player_list_model.hpp
        examples/simple-text-editor/player.cpp
        examples/simple-text-editor/player.hpp)

target_link_libraries(trundle-examples trundle)