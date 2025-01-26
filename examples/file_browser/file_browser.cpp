//
// Created by James Pickering on 1/2/25.
//

#include "file_browser.hpp"

#include "trundle/widget/label_widget.hpp"
#include "trundle/widget/text_field_widget.hpp"

#include <trundle/model/filter_model.hpp>
#include <trundle/model/item_model.hpp>
#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/view/text_view.hpp>
#include <trundle/view/tree_view.hpp>
#include <trundle/widget/tree_widget.hpp>
#include <trundle/widget/widget.hpp>
#include <trundle/widget/window_widget.hpp>

#include <filesystem>

namespace examples {

using namespace trundle;

struct FileNode {
    std::wstring name{};
    std::filesystem::path path{};
    std::vector<std::unique_ptr<FileNode>> children{};
};

struct FileBrowserModel : ItemModel {
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
            return createIndex(row, _root);
        }
        const auto node = static_cast<FileNode*>(parent.data);
        return createIndex(row, node->children[row].get());
    }

    [[nodiscard]] auto hasChildren(const Index index) const -> bool override {
        const auto node = static_cast<FileNode*>(index.data);
        return is_directory(node->path);
    }

    auto loadChildren(Index parent) -> void override {
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

private:
    FileNode* _root;
};

auto FileBrowser::run() -> void {
    const auto path = std::filesystem::path{"/Users/jamespickering/Documents/dev"};

    auto pathToWString = [](const auto& path) {
        const auto str = path.string();
        return std::wstring{str.begin(), str.end()};
    };

    const auto root = std::make_unique<FileNode>(pathToWString(path.filename()), path);
    auto model = FileBrowserModel{root.get()};
    auto filterModel = FilterModel{};

    filterModel.setSourceModel(&model);

    /**
     * Setup UI
     */
    auto window = ScreenWidget{};
    window.setTitle(L"File Browser");

    const auto treeView = window.addChild<TreeView>();
    treeView->setTitle(L"Browser");
    treeView->tree()->setModel(&filterModel);

    const auto detailsFrame = window.addChild<FrameWidget>();
    detailsFrame->setTitle(L"Details");
    detailsFrame->setFrameStyle(FrameStyle::Window);

    const auto nameLabel = detailsFrame->addChild<LabelWidget>();

    treeView->tree()->setOnSelectionChanged([&detailsFrame, &nameLabel](auto tree) {
        const auto idx = tree->selectedIndex();
        const auto node = static_cast<FileNode*>(idx.data);
        nameLabel->clear();
        nameLabel->setText(L"File Name: " + node->name);
    });

    const auto log = window.addChild<TextView>();
    log->setTitle(L"Log");
    log->setFrameStyle(FrameStyle::Window);

    Trundle::setOnLogUpdated([&log]() {
        auto text = std::wstring{};
        auto i = 0;
        for (const auto& entry : Trundle::log()) {
            text += entry;
            text += L"\n";
        }
        log->textField()->setText(text);
        log->textField()->scrollToEnd();
    });

    treeView->addLayoutConstraints({{LayoutAttr::Left, &window, LayoutAttr::Left, 2},
                                    {LayoutAttr::Top, &window, LayoutAttr::Top, 2},
                                    {LayoutAttr::Width, 40},
                                    {LayoutAttr::Height, 40}});

    detailsFrame->addLayoutConstraints({{LayoutAttr::Left, treeView, LayoutAttr::Right, 2},
                                        {LayoutAttr::Top, treeView, LayoutAttr::Top},
                                        {LayoutAttr::Width, 40},
                                        {LayoutAttr::Height, 20}});

    nameLabel->addLayoutConstraints({{LayoutAttr::Left, detailsFrame, LayoutAttr::Left, 2},
                                     {LayoutAttr::Top, detailsFrame, LayoutAttr::Top, static_cast<double>(detailsFrame->headerHeight())},
                                     {LayoutAttr::Right, detailsFrame, LayoutAttr::Right, -2},
                                     {LayoutAttr::Height, 2}});

    log->addLayoutConstraints({{LayoutAttr::Left, detailsFrame, LayoutAttr::Right, 2},
                               {LayoutAttr::Top, detailsFrame, LayoutAttr::Top},
                               {LayoutAttr::Width, 50},
                               {LayoutAttr::Height, 40}});

    while (true) {
        Keyboard::poll();
        window.performUpdate();
        window.performRender();
        Trundle::refresh();
    }
}

}