cmake_minimum_required(VERSION 3.27)
project(trundle-examples)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(trundle)

add_executable(trundle-examples main.cpp
        giants_players.cpp
        giants_players.hpp)

target_link_libraries(trundle-examples trundle)