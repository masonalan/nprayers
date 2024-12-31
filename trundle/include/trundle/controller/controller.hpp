//
// Created by James Pickering on 12/30/24.
//

#pragma once

namespace trundle {

struct Widget;

struct Controller {
    [[nodiscard]] virtual auto mainWidget() -> Widget* = 0;
};

}