//
// Created by James Pickering on 12/29/24.
//

#pragma once

#include <string>

namespace trundle {

struct ListModel {
    virtual ~ListModel();

    [[nodiscard]] virtual auto rowCount() const -> unsigned int = 0;
    [[nodiscard]] virtual auto rowText(unsigned int row) const -> const std::wstring& = 0;
};

}
