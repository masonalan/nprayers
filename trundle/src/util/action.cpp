//
// Created by James Pickering on 12/28/24.
//

#include <trundle/util/action.hpp>

namespace trundle {

Action::Action(trundle::Key key, std::string title, std::function<void(Widget*)>&& callback) :
    key{key},
    title{std::move(title)},
    callback{callback} {
}

}