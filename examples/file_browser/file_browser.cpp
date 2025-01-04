//
// Created by James Pickering on 1/2/25.
//

#include "file_browser.hpp"

#include <trundle/model/tree_model.hpp>
#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/widget/tree_widget.hpp>
#include <trundle/widget/widget.hpp>
#include <trundle/widget/window_widget.hpp>

#include <filesystem>

namespace examples {

using namespace trundle;

struct FileNode {
    std::wstring name;
    std::filesystem::path path;
    std::vector<FileNode> children;
};

struct FileBrowserModel : TreeModel {
    explicit FileBrowserModel(FileNode* root) :
        _root{root} {
    }

    [[nodiscard]] auto rowCount(const Index parent) const -> unsigned int override {
        if (!parent.data) {
            return 1;
        }
        const auto node = static_cast<FileNode*>(parent.data);
        return node->children.size();
    }

    [[nodiscard]] auto rowText(const Index index) const -> const std::wstring& override {
        if (const auto node = static_cast<FileNode*>(index.data)) {
            return node->name;
        }

        throw std::runtime_error("FileBrowserModel::rowText: index out of range");
    }

    [[nodiscard]] auto rowDecoration(Index index) const -> const std::wstring& override {
        const auto node = static_cast<FileNode*>(index.data);
        return is_directory(node->path) ? Unicode::FolderOpened : String::Space;
    }

    [[nodiscard]] auto index(const Index parent, const unsigned int row) const -> Index override {
        if (!parent.data) {
            return Index{row, _root};
        }
        const auto node = static_cast<FileNode*>(parent.data);
        return Index{row, &node->children[row]};
    }

    [[nodiscard]] auto hasChildren(const Index index) const -> bool override {
        const auto node = static_cast<FileNode*>(index.data);
        return is_directory(node->path);
    }

private:
    FileNode* _root;
};

auto FileBrowser::run() -> void {
    const auto path = std::filesystem::path{"/Users/jamespickering/Documents/dev"};

    auto pathToWString = [](const auto& path) {
        const auto str = path.string();
        return std::wstring{str.begin(), str.end()};
    };

    auto root = std::make_unique<FileNode>(pathToWString(path.filename()), path);

    for (const auto& entry : std::filesystem::directory_iterator{path}) {
        root->children.push_back(FileNode{pathToWString(entry.path().filename()), entry.path()});
    }

    /**
     * Setup UI
     */
    auto window = WindowWidget{};
    window.setTitle("File Browser");

    const auto treeFrame = window.addChild<FrameWidget>();
    treeFrame->setTitle("Browser");
    treeFrame->setTitleBarStyle(TitleBarStyle::MultiLine);

    auto model = FileBrowserModel{root.get()};

    const auto treeWidget = treeFrame->addChild<TreeWidget>();
    treeWidget->setModel(&model);
    treeWidget->setOnExpand([&pathToWString](auto t) {
        const auto node = static_cast<FileNode*>(t->selectedIndex().data);
        for (auto& child : node->children) {
            if (is_directory(child.path)) {
                child.children.clear();
                for (const auto& entry : std::filesystem::directory_iterator{child.path}) {
                    child.children.push_back(FileNode{pathToWString(entry.path().filename()), entry.path()});
                }
            }
        }
    });

    treeFrame->addLayoutConstraints({{LayoutAttribute::Left, &window, LayoutAttribute::Left, 3},
                                     {LayoutAttribute::Top, &window, LayoutAttribute::Top, 2},
                                     {LayoutAttribute::Width, 40},
                                     {LayoutAttribute::Height, &window, LayoutAttribute::Height, -4}});

    treeWidget->addLayoutConstraints({{LayoutAttribute::Left, treeFrame, LayoutAttribute::Left, 2},
                                      {LayoutAttribute::Top, treeFrame, LayoutAttribute::Top, 3},
                                      {LayoutAttribute::Right, treeFrame, LayoutAttribute::Right, -2},
                                      {LayoutAttribute::Bottom, treeFrame, LayoutAttribute::Bottom, -1}});

    while (true) {
        Keyboard::poll();
        window.performUpdate();
        window.performRender();
        Trundle::refresh();
    }
}
}