//
// Created by James Pickering on 1/25/25.
//

#include "util.hpp"

namespace examples {

auto Util::pathToWideString(const std::filesystem::path& path) -> std::wstring {
    const auto str = path.string();
    return {str.begin(), str.end()};
}

}