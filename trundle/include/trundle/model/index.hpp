//
// Created by James Pickering on 1/25/25.
//

#pragma once

#include <functional>

namespace trundle {

struct Model;

struct Index {
    Index(const Model* model, unsigned int row, void* data) :
        model(model),
        row(row),
        data(data) {}

    const Model* model{nullptr};
    unsigned int row{0};
    void* data{nullptr};
};

}

template <>
struct std::hash<trundle::Index> {
    std::size_t operator()(const trundle::Index& s) const noexcept {
        const std::size_t h1 = std::hash<unsigned int>{}(s.row);
        const std::size_t h2 = std::hash<void*>{}(s.data);
        return h1 ^ (h2 << 1);
    }
};
