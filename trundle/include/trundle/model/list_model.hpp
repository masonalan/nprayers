//
// Created by James Pickering on 12/29/24.
//

#pragma once

#include <string>

namespace trundle {

struct ListModel {
    virtual ~ListModel();

    virtual auto rowCount() const -> unsigned int = 0;
    virtual auto rowText(unsigned int row) const -> const std::string& = 0;
};

}
