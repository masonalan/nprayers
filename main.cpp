#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/widget/action_bar_widget.hpp>
#include <trundle/widget/divider_widget.hpp>
#include <trundle/widget/frame_widget.hpp>
#include <trundle/widget/list_widget.hpp>
#include <trundle/widget/text_area_widget.hpp>
#include <trundle/widget/text_field_widget.hpp>
#include <trundle/widget/window_widget.hpp>

#include "giants_players.hpp"

using namespace trundle;

auto keyboardTester() -> void {
    Trundle::init();

    while (true) {
        auto c = Trundle::currChar();
        if (c >= 0) {
            Trundle::print(std::to_string(c));
            Trundle::print(std::string{", "});
        }
    }
}

auto main(int argc, char* argv[]) -> int {
    if (argc == 2) {
        if (std::string{argv[1]} == "-k") {
            keyboardTester();
            return 0;
        }
    }

    //    Trundle::init();
    //    Keyboard::init();

    //    while (true) {
    //        Keyboard::poll();
    //        if (Keyboard::currKey() == Key::Enter) {
    //            break;
    //        }
    //    }

    giantsplayers::main();

    //
    //
    //    Trundle::init();
    //    Keyboard::init();
    //
    //    while (true) {
    //        Keyboard::poll();
    //        if (Keyboard::getKey() == Key::Enter) {
    //            break;
    //        }
    //    }
    //
    //    auto window = std::make_unique<WindowWidget>();
    //    window->addLayoutConstraint({LayoutAttribute::Left, 0});
    //    window->addLayoutConstraint({LayoutAttribute::Top, 0});
    //    window->addLayoutConstraint({LayoutAttribute::Width, 300});
    //    window->addLayoutConstraint({LayoutAttribute::Height, 300});
    //
    //    Keyboard::onKeyPress([&window]() {
    //        window->performUpdate();
    //    });
    //
    //    auto left = window->addChild<FrameWidget>();
    //    left->addLayoutConstraint({LayoutAttribute::Left, window.get(), LayoutAttribute::Left, 15});
    //    left->addLayoutConstraint({LayoutAttribute::Top, window.get(), LayoutAttribute::Top, 10});
    //    left->addLayoutConstraint({LayoutAttribute::Width, 20});
    //    left->addLayoutConstraint({LayoutAttribute::Height, 10});
    //    left->setTitle("Single");
    //    left->setTitleBarStyle(TitleBarStyle::SingleLine);
    //    left->setFocused(true);
    //
    //    auto actionBar = left->addChild<ActionBarWidget>();
    //    actionBar->addLayoutConstraint({LayoutAttribute::Left, left, LayoutAttribute::Left, 1});
    //    actionBar->addLayoutConstraint({LayoutAttribute::Bottom, left, LayoutAttribute::Bottom, -1});
    //    actionBar->addLayoutConstraint({LayoutAttribute::Width, left, LayoutAttribute::Width, -2});
    //    actionBar->addLayoutConstraint({LayoutAttribute::Height, actionBar, LayoutAttribute::Width, [&actionBar](auto width) {
    //                                        const auto cols = static_cast<int>(width) / 10;
    //                                        const auto count = actionBar->actionsSize() - 1;
    //                                        return static_cast<double>(count / cols + 1);
    //                                    }});
    //
    //    auto middle = window->addChild<FrameWidget>();
    //    middle->addLayoutConstraint({LayoutAttribute::Left, left, LayoutAttribute::Right, 2});
    //    middle->addLayoutConstraint({LayoutAttribute::Top, left, LayoutAttribute::Top});
    //    middle->addLayoutConstraint({LayoutAttribute::Width, 35});
    //    middle->addLayoutConstraint({LayoutAttribute::Height, 18});
    //    middle->setTitle("Short Bio");
    //    middle->setTitleBarStyle(TitleBarStyle::DoubleLine);
    //
    //    auto actionBarMiddle = middle->addChild<ActionBarWidget>();
    //    actionBarMiddle->addLayoutConstraint({LayoutAttribute::Left, middle, LayoutAttribute::Left, 1});
    //    actionBarMiddle->addLayoutConstraint({LayoutAttribute::Bottom, middle, LayoutAttribute::Bottom, -1});
    //    actionBarMiddle->addLayoutConstraint({LayoutAttribute::Right, middle, LayoutAttribute::Right, -1});
    //    actionBarMiddle->addLayoutConstraint({LayoutAttribute::Height, actionBarMiddle, LayoutAttribute::Width, [&actionBarMiddle](auto width) {
    //                                              const auto cols = static_cast<int>(width) / 10;
    //                                              const auto count = actionBarMiddle->actionsSize() - 1;
    //                                              return static_cast<double>(count / cols + 1);
    //                                          }});
    //
    //    auto inputMiddle = middle->addChild<TextFieldWidget>();
    //    inputMiddle->addLayoutConstraint({LayoutAttribute::Left, middle, LayoutAttribute::Left, 2});
    //    inputMiddle->addLayoutConstraint({LayoutAttribute::Top, middle, LayoutAttribute::Top, 1});
    //    inputMiddle->addLayoutConstraint({LayoutAttribute::Bottom, actionBarMiddle, LayoutAttribute::Top, -1});
    //    inputMiddle->addLayoutConstraint({LayoutAttribute::Right, middle, LayoutAttribute::Right, -2});
    //
    //    auto right = window->addChild<FrameWidget>();
    //    right->addLayoutConstraint({LayoutAttribute::Left, left, LayoutAttribute::Left});
    //    right->addLayoutConstraint({LayoutAttribute::Top, left, LayoutAttribute::Bottom, 1});
    //    right->addLayoutConstraint({LayoutAttribute::Width, left, LayoutAttribute::Width});
    //    right->addLayoutConstraint({LayoutAttribute::Height, 15});
    //    right->setTitle("Multi");
    //    right->setTitleBarStyle(TitleBarStyle::MultiLine);
    //
    //    auto smallList = right->addChild<ListWidget>();
    //    smallList->addLayoutConstraint({LayoutAttribute::Left, right, LayoutAttribute::Left, 1});
    //    smallList->addLayoutConstraint({LayoutAttribute::Right, right, LayoutAttribute::Right, -1});
    //    smallList->addLayoutConstraint({LayoutAttribute::Top, right, LayoutAttribute::Top, 3});
    //    smallList->addLayoutConstraint({LayoutAttribute::Bottom, right, LayoutAttribute::Bottom, -1});
    //    smallList->addItem("Hey");
    //    smallList->addItem("Hello");
    //    smallList->addItem("Yellow");
    //
    //    auto wide = window->addChild<FrameWidget>();
    //    wide->addLayoutConstraint({LayoutAttribute::Left, middle, LayoutAttribute::Right, 2});
    //    wide->addLayoutConstraint({LayoutAttribute::Top, left, LayoutAttribute::Top});
    //    wide->addLayoutConstraint({LayoutAttribute::Width, left, LayoutAttribute::Width, 0, 4});
    //    wide->addLayoutConstraint({LayoutAttribute::Height, 25});
    //    wide->setTitle("Wide");
    //    wide->setTitleBarStyle(TitleBarStyle::MultiLine);
    //
    //    auto wideActionBar = wide->addChild<ActionBarWidget>();
    //    wideActionBar->addLayoutConstraint({LayoutAttribute::Left, wide, LayoutAttribute::Left, 1});
    //    wideActionBar->addLayoutConstraint({LayoutAttribute::Bottom, wide, LayoutAttribute::Bottom, 0});
    //    wideActionBar->addLayoutConstraint({LayoutAttribute::Right, wide, LayoutAttribute::Right, -1});
    //    wideActionBar->addLayoutConstraint({LayoutAttribute::Height, wideActionBar, LayoutAttribute::Width, [&wideActionBar](auto width) {
    //                                            if (!wideActionBar->visible()) {
    //                                                return 0.0;
    //                                            }
    //                                            const auto cols = static_cast<int>(width) / 10;
    //                                            const auto count = wideActionBar->actionsSize() - 1;
    //                                            return static_cast<double>(count / cols + 2);
    //                                        }});
    //
    //    auto wideList = wide->addChild<ListWidget>();
    //    wideList->addLayoutConstraint({LayoutAttribute::Left, wide, LayoutAttribute::Left, 2});
    //    wideList->addLayoutConstraint({LayoutAttribute::Width, 20});
    //    wideList->addLayoutConstraint({LayoutAttribute::Top, wide, LayoutAttribute::Top, 3});
    //    wideList->addLayoutConstraint({LayoutAttribute::Bottom, wide, LayoutAttribute::Bottom, -1});
    //    wideList->addItem("Daniel Jones");
    //    wideList->addItem("Malik Nabers");
    //    wideList->addItem("Tyrone Tracy Jr.");
    //    wideList->addItem("Tyler Nubin");
    //    wideList->addItem("Dru Phillips");
    //    wideList->addItem("Cam Ward");
    //    wideList->addAction(Key::OptR, "Add", [](auto list) {
    //        static_cast<ListWidget*>(list)->addItem("New");
    //    });
    //    wideList->addAction(Key::Delete, std::string{"Remove"}, [](auto list) {
    //        //static_cast<ListWidget*>(list)->addItem("yunkkk");
    //    });
    //    wideList->addAction(Key::Up, "Up", [](auto widget) {
    //        auto list = static_cast<ListWidget*>(widget);
    //        list->selectRow(std::max(list->selectedRow() - 1, 0));
    //    });
    //    wideList->addAction(Key::Down, "Down", [](auto widget) {
    //        auto list = static_cast<ListWidget*>(widget);
    //        list->selectRow(std::min(list->selectedRow() + 1, list->rowCount() - 1));
    //    });
    //
    //    wideActionBar->displayActions(wideList->actions());
    //
    //    auto wideDivider = wide->addChild<DividerWidget>();
    //    wideDivider->addLayoutConstraint({LayoutAttribute::Left, wideList, LayoutAttribute::Right});
    //    wideDivider->addLayoutConstraint({LayoutAttribute::Top, wide, LayoutAttribute::Top, 2});
    //    wideDivider->addLayoutConstraint({LayoutAttribute::Bottom, wideActionBar, LayoutAttribute::Top});
    //    wideDivider->addLayoutConstraint({LayoutAttribute::Width, 1});
    //
    //    auto wideTextArea = wide->addChild<TextAreaWidget>();
    //    wideTextArea->addLayoutConstraint({LayoutAttribute::Left, wideDivider, LayoutAttribute::Right, 1});
    //    wideTextArea->addLayoutConstraint({LayoutAttribute::Top, wide, LayoutAttribute::Top, 3});
    //    wideTextArea->addLayoutConstraint({LayoutAttribute::Bottom, wideActionBar, LayoutAttribute::Top});
    //    wideTextArea->addLayoutConstraint({LayoutAttribute::Right, wide, LayoutAttribute::Right, -1});
    //    wideTextArea->setText("*Daniel Jones*\n\nDaniel Jones was a menace to society for many years. He was a controversial figure, as many people loved him but many people hated him. One day, he will either go to heaven or hell. I could not tell you which.");
    //
    //    window->performUpdate();
    //
    //    Keyboard::writeToBuffer(true);
    //
    //    while (true) {
    //        Keyboard::poll();
    //        window->performRender();
    //        Trundle::refresh();
    //    }

    return 0;
}
