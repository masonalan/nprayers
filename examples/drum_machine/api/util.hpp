//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include <filesystem>
#include <string>

namespace examples {

struct Util {
    static auto pathToWideString(const std::filesystem::path& path) -> std::wstring;
};

}
