//
// Created by James Pickering on 1/12/25.
//

#pragma once

#include <trundle/model/index.hpp>
#include <trundle/model/model.hpp>

#include <glm/vec2.hpp>

#include <filesystem>
#include <functional>
#include <string>

namespace trundle {

struct ItemModel : Model {
    [[nodiscard]] virtual auto rowText(Index index) const -> const std::wstring& = 0;
    [[nodiscard]] virtual auto rowDecoration(Index index) const -> const std::wstring& = 0;
};

}