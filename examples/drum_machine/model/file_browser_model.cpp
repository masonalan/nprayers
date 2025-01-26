//
// Created by James Pickering on 1/22/25.
//

#include "file_browser_model.hpp"

#include <trundle/util/unicode.hpp>

namespace examples {

FileBrowserModel::FileBrowserModel(FileNode* root) :
    _root{root} {
}

auto FileBrowserModel::rowCount(const Index parent) const -> unsigned int {
    if (!parent.data) {
        return 1;
    }
    const auto node = static_cast<FileNode*>(parent.data);
    return node->children.size();
}

auto FileBrowserModel::rowText(const Index index) const -> const std::wstring& {
    if (const auto node = static_cast<FileNode*>(index.data)) {
        return node->name;
    }

    throw std::runtime_error("FileBrowserModel::rowText: index out of range");
}

auto FileBrowserModel::rowDecoration(Index index) const -> const std::wstring& {
    const auto node = static_cast<FileNode*>(index.data);
    return is_directory(node->path) ? Unicode::FolderOpened : String::Space;
}

auto FileBrowserModel::index(Index parent, unsigned int row) const -> Index {
    if (!parent.data) {
        return createIndex(row, _root);
    }
    const auto node = static_cast<FileNode*>(parent.data);
    return createIndex(row, node->children[row].get());
}

auto FileBrowserModel::hasChildren(const Index index) const -> bool {
    const auto node = static_cast<FileNode*>(index.data);
    return is_directory(node->path);
}

auto FileBrowserModel::loadChildren(Index parent) -> void {
    auto pathToWString = [](const auto& path) {
        const auto str = path.string();
        return std::wstring{str.begin(), str.end()};
    };

    const auto node = static_cast<FileNode*>(parent.data);
    if (is_directory(node->path)) {
        auto row = 0;
        for (const auto& entry : std::filesystem::directory_iterator{node->path}) {
            const auto path = pathToWString(entry.path().filename());
            if (row >= node->children.size()) {
                node->children.push_back(std::make_unique<FileNode>(path, entry.path()));
            } else if (node->children[row]->path != entry.path().filename()) {
                node->children[row]->name = path;
                node->children[row]->path = entry.path();
            }

            ++row;
        }
    }

    dataChanged();
}

}