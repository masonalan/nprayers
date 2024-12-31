//
// Created by James Pickering on 12/29/24.
//

#include "giants_players.hpp"

#include <trundle/controller/list_controller.hpp>
#include <trundle/controller/text_editor_controller.hpp>
#include <trundle/controller/window_controller.hpp>
#include <trundle/model/list_model.hpp>
#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/util/layout_attribute.hpp>
#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/frame_widget.hpp>
#include <trundle/widget/list_widget.hpp>
#include <trundle/widget/text_field_widget.hpp>
#include <trundle/widget/window_widget.hpp>

#include <vector>

using namespace trundle;

namespace giantsplayers {

struct Player {
    std::string name;
    std::string desc;
};

struct Data {
    std::vector<Player> players{};
};

struct PlayerListModel : public ListModel {
    PlayerListModel(std::vector<Player>* players) :
        _players{players} {
    }

    auto rowCount() const -> unsigned int override {
        return static_cast<unsigned int>(_players->size());
    }

    auto rowText(unsigned int row) const -> const std::string& override {
        return _players->at(row).name;
    }

private:
    std::vector<Player>* _players;
};

auto main() -> void {
    auto d = Data{};
    d.players.push_back(Player{"Daniel Jones",
                               "*Daniel Jones*\n\n"
                               ""
                               "A lot of people initially thought Daniel Jones would be the future of football as we know it. Towering over his competition, he threw touchdown after touchdown, until the fateful day when he smashed his head into the grown and tore his ACL at the same time. He was never the same after that. The New York Giants ruthlessly cast him off into the streets, and there he remains, cold, homeless, and without healthcare."});
    d.players.push_back(Player{"Malik Nabers",
                               "*Malik Nabers*\n\n"
                               ""
                               "Also going by The Savior, Jesus, The Goat, Odell but better, Jamar but better, Malik Nabers has done miracles on me and the New York Giants organization as a whole. He has singlehandedly saved Brian 'The Whisperer' Daboll's job."});

    Trundle::init();
    Keyboard::init();

    auto window = WindowController{"New York Giants Power Rankings"};

    auto listController = ListController{&window};
    listController.frame()->setTitle("Players");
    listController.list()->setModel<PlayerListModel>(&d.players);

    auto textEditorController = TextEditorController{&window};
    textEditorController.frame()->setTitle("Description");

    listController.mainWidget()->addLayoutConstraint({LayoutAttribute::Left, window.mainWidget(), LayoutAttribute::Left, 3});
    listController.mainWidget()->addLayoutConstraint({LayoutAttribute::Top, window.mainWidget(), LayoutAttribute::Top, 2});
    listController.mainWidget()->addLayoutConstraint({LayoutAttribute::Width, 30});
    listController.mainWidget()->addLayoutConstraint({LayoutAttribute::Height, 40});

    textEditorController.mainWidget()->addLayoutConstraint({LayoutAttribute::Left, listController.mainWidget(), LayoutAttribute::Right, 1});
    textEditorController.mainWidget()->addLayoutConstraint({LayoutAttribute::Top, listController.mainWidget(), LayoutAttribute::Top});
    textEditorController.mainWidget()->addLayoutConstraint({LayoutAttribute::Width, 100});
    textEditorController.mainWidget()->addLayoutConstraint({LayoutAttribute::Height, listController.mainWidget(), LayoutAttribute::Height});

    listController.list()->setAddCallback([&d](auto widget, auto row) {
        d.players.insert(d.players.begin() + row, Player{"New Player", ""});
    });

    listController.list()->setRemoveCallback([&d](auto widget, auto row) {
        d.players.erase(d.players.begin() + row);
    });

    listController.list()->setSelectionChangedCallback([&textEditorController, &d](auto list, auto row) {
        textEditorController.textEditor()->setText(d.players.at(row).desc);
    });

    textEditorController.textEditor()->setText(d.players.at(0).desc);

    while (true) {
        Keyboard::poll();
        window.mainWidget()->performUpdate();
        window.mainWidget()->performRender();
        Trundle::refresh();
    }
}

}