//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include <filesystem>

namespace examples {

struct Settings {
    Settings();
    ~Settings();

    auto setBrowserPath(std::filesystem::path path) -> void;

    [[nodiscard]] auto browserPath() const -> const std::filesystem::path&;

private:
    std::filesystem::path _browserPath;
};

}
