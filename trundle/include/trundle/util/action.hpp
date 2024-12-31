//
// Created by James Pickering on 12/28/24.
//

#pragma once

#include <trundle/util/keyboard.hpp>

#include <functional>

namespace trundle {

struct Widget;

struct Action {
    Action(Key key, std::string title, std::function<void(Widget*)>&& callback);

    Key key;
    std::string title;
    std::function<void(Widget*)> callback;
};

}