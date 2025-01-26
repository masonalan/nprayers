//
// Created by James Pickering on 1/25/25.
//

#pragma once

namespace trundle {

struct IndexState {
    IndexState() :
        visible{true},
        start{0},
        length{0},
        _expanded{false} {}

    auto setExpanded(bool expanded) -> void {
        _expanded = expanded;
    }

    [[nodiscard]] auto expanded() const -> bool {
        return _expanded;
    }

    bool visible;
    unsigned int start;
    unsigned int length;

private:
    bool _expanded;
};

inline auto operator==(const Index& lhs, const Index& rhs) -> bool {
    return lhs.data == rhs.data &&
           lhs.row == rhs.row &&
           lhs.model == rhs.model;
}

}
