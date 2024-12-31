cmake_minimum_required(VERSION 3.27)

find_library(trundle ncurses)
find_package(glm CONFIG REQUIRED)

add_library(
        trundle
        include/trundle/trundle.hpp
        src/trundle.cpp
        include/trundle/util/color_pair.hpp
        include/trundle/widget/widget.hpp
        src/widget/widget.cpp
        include/trundle/util/layout_constraint.hpp
        include/trundle/util/layout_constraint_result.hpp
        include/trundle/util/layout_attribute.hpp
        include/trundle/widget/frame_widget.hpp
        src/widget/frame_widget.cpp
        src/util/layout_constraint.cpp
        src/util/unicode.cpp
        include/trundle/util/unicode.hpp
        include/trundle/widget/action_bar_widget.hpp
        src/widget/action_bar_widget.cpp
        include/trundle/util/keyboard.hpp
        src/util/keyboard.cpp
        src/util/layout_attribute.cpp
        include/trundle/widget/list_widget.hpp
        src/widget/list_widget.cpp
        include/trundle/widget/divider_widget.hpp
        src/widget/divider_widget.cpp
        include/trundle/widget/text_area_widget.hpp
        src/widget/text_area_widget.cpp
        include/trundle/widget/text_field_widget.hpp
        src/widget/text_field_widget.cpp
        include/trundle/widget/window_widget.hpp
        src/widget/window_widget.cpp
        include/trundle/util/action.hpp
        include/trundle/util/key.hpp
        src/util/key.cpp
        src/util/action.cpp
        include/trundle/model/list_model.hpp
        src/model/list_model.cpp
        include/trundle/controller/window_controller.hpp
        include/trundle/controller/list_controller.hpp
        src/controller/window_controller.cpp
        include/trundle/controller/controller.hpp
        src/controller/list_controller.cpp
        include/trundle/controller/text_editor_controller.hpp
        src/controller/text_editor_controller.cpp
)

target_include_directories(trundle PUBLIC include)

target_link_libraries(trundle PUBLIC ncurses)
target_link_libraries(trundle PUBLIC glm::glm)
