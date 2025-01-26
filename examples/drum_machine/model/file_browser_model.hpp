//
// Created by James Pickering on 1/22/25.
//

#pragma once

#include <trundle/model/item_model.hpp>

#include <filesystem>
#include <string>
#include <vector>

using namespace trundle;

namespace examples {

struct FileNode {
    std::wstring name{};
    std::filesystem::path path{};
    std::vector<std::unique_ptr<FileNode>> children{};
};

struct FileBrowserModel : ItemModel {
    explicit FileBrowserModel(FileNode* root);

    [[nodiscard]] auto rowCount(Index parent) const -> unsigned int override;
    [[nodiscard]] auto rowText(Index index) const -> const std::wstring& override;
    [[nodiscard]] auto rowDecoration(Index index) const -> const std::wstring& override;
    [[nodiscard]] auto index(Index parent, unsigned int row) const -> Index override;
    [[nodiscard]] auto hasChildren(Index index) const -> bool override;

    auto loadChildren(Index parent) -> void override;

private:
    FileNode* _root;
};

}