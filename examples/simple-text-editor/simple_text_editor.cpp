//
// Created by James Pickering on 12/29/24.
//

#include "simple_text_editor.hpp"

#include "../../trundle/include/trundle/view/prompt_view.hpp"
#include "player.hpp"
#include "player_list_model.hpp"

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/layout_attribute.hpp>
#include <trundle/view/list_view.hpp>
#include <trundle/view/text_view.hpp>
#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/frame_widget.hpp>
#include <trundle/widget/list_widget.hpp>
#include <trundle/widget/text_field_widget.hpp>
#include <trundle/widget/window_widget.hpp>

#include <vector>

using namespace trundle;

namespace examples {

struct Data {
    std::vector<Player> players{};
};

auto SimpleTextEditor::run() -> void {
    auto d = Data{};
    d.players.push_back(Player{L"Daniel Jones",
                               L"*Daniel Jones*\n\n"
                               ""
                               "A lot of people initially thought Daniel Jones would be the future of football as we know it. Towering over his competition, he threw touchdown after touchdown, until the fateful day when he smashed his head into the grown and tore his ACL at the same time. He was never the same after that. The New York Giants ruthlessly cast him off into the streets, and there he remains, cold, homeless, and without healthcare."});
    d.players.push_back(Player{L"Malik Nabers",
                               L"*Malik Nabers*\n\n"
                               ""
                               "Also going by The Savior, Jesus, The Goat, Odell but better, Jamar but better, Malik Nabers has done miracles on me and the New York Giants organization as a whole. He has singlehandedly saved Brian 'The Whisperer' Daboll's job."});

    Trundle::init();
    Keyboard::init();

    auto window = WindowWidget{};
    window.setTitle("New York Giants Power Rankings");

    auto listView = window.addChild<ListView>();
    listView->setTitle("Players");
    listView->setFlags(ListViewFlag::Editable);
    listView->list()->setModel<PlayerListModel>(&d.players);

    auto textView = window.addChild<TextView>();
    textView->setTitle("Description");
    textView->textField()->setText(d.players.at(0).desc);

    listView->setOnAdd([&d, &listView, &window, &textView](auto, auto row) {
        const auto player = d.players.insert(d.players.begin() + row, {L"New Player", L""});
        listView->list()->selectRow(row);
        textView->textField()->setText(player->desc);

        Prompt::createWithTextField(
            &window,
            "New Player",
            L"Enter a player's name:",
            L"New Player",
            [&d, &listView](auto p) {
                d.players[listView->list()->selectedRow()].name = p->value();
                listView->list()->clear();
                p->window()->setFocused(listView);
            },
            [&listView](auto p) {
                p->window()->setFocused(listView);
            });
    });

    listView->setOnRemove([&d, &window, &listView](auto, auto row) {
        Prompt::create(
            &window,
            "Delete Player",
            L"Are you sure you want to delete " + d.players[row].name + L"?",
            [&d, &listView](auto p) {
                if (const auto itr = d.players.erase(d.players.begin() + listView->list()->selectedRow()); itr != d.players.end()) {
                    listView->list()->selectRow(static_cast<int>(std::distance(d.players.begin(), itr)));
                } else if (d.players.begin() != d.players.end()) {
                    listView->list()->selectRow(0);
                }
                listView->list()->clear();
                p->window()->setFocused(listView);
            },
            [&listView](auto p) {
                p->window()->setFocused(listView);
            });
    });

    listView->list()->setOnSelectionChanged([&textView, &d](auto list, auto oldRow, auto newRow) {
        d.players.at(oldRow).desc = textView->textField()->text();
        textView->textField()->setText(d.players.at(newRow).desc);
    });

    listView->addLayoutConstraints({{LayoutAttribute::Left, &window, LayoutAttribute::Left, 3},
                                    {LayoutAttribute::Top, &window, LayoutAttribute::Top, 2},
                                    {LayoutAttribute::Width, 30},
                                    {LayoutAttribute::Height, 40}});

    textView->addLayoutConstraints({{LayoutAttribute::Left, listView, LayoutAttribute::Right, 1},
                                    {LayoutAttribute::Top, listView, LayoutAttribute::Top},
                                    {LayoutAttribute::Width, 100},
                                    {LayoutAttribute::Height, listView, LayoutAttribute::Height}});

    while (true) {// NOLINT
        Keyboard::poll();
        window.performUpdate();
        window.performRender();
        Trundle::refresh();
    }
}
}