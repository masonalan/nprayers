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
        include/trundle/view/list_view.hpp
        src/view/list_view.cpp
        include/trundle/view/text_view.hpp
        src/view/text_view.cpp
        include/trundle/view/prompt_view.hpp
        src/view/prompt_view.cpp
        include/trundle/widget/label_widget.hpp
        src/widget/label_widget.cpp
        include/trundle/util/text.hpp
        src/util/text.cpp
        include/trundle/util/enum_math.hpp
        include/trundle/widget/tree_widget.hpp
        include/trundle/model/tree_model.hpp
        src/widget/tree_widget.cpp
        src/model/tree_model.cpp
        include/trundle/widget/scroll_bar_widget.hpp
        src/widget/scroll_bar_widget.cpp
        include/trundle/view/tree_view.hpp
        src/view/tree_view.cpp
        include/trundle/model/filter_model.hpp
        src/model/filter_model.cpp
        include/trundle/model/item_model.hpp
        src/model/item_model.cpp
        include/trundle/view/search_view.hpp
        src/view/search_view.cpp
        include/trundle/view/view.hpp
        src/view/view.cpp
        include/trundle/widget/meter_widget.hpp
        src/widget/meter_widget.cpp
        include/trundle/widget/slider_widget.hpp
        src/widget/slider_widget.cpp
        include/trundle/widget/picker_widget.hpp
        src/widget/picker_widget.cpp
        include/trundle/model/widget_model.hpp
        src/model/widget_model.cpp
        include/trundle/model/model.hpp
        src/model/model.cpp
        include/trundle/model/index.hpp
        include/trundle/model/index_state.hpp
        include/trundle/renderer/item_render_delegate.hpp
        include/trundle/renderer/header_render_delegate.hpp
        include/trundle/renderer/abstract_header_render_delegate.hpp
        src/renderer/abstract_header_render_delegate.cpp
        include/trundle/renderer/tree_item_render_delegate.hpp
        src/renderer/tree_item_render_delegate.cpp
        include/trundle/renderer/list_item_render_delegate.hpp
        src/renderer/list_item_render_delegate.cpp
)

target_include_directories(trundle PUBLIC include)

target_link_libraries(trundle PUBLIC ncurses)
target_link_libraries(trundle PUBLIC glm::glm)
