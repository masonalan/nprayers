//
// Created by James Pickering on 1/25/25.
//

#include "settings.hpp"

namespace examples {

Settings::Settings() = default;
Settings::~Settings() = default;

auto Settings::setBrowserPath(std::filesystem::path path) -> void {
    _browserPath = std::move(path);
}

auto Settings::browserPath() const -> const std::filesystem::path& {
    return _browserPath;
}

}