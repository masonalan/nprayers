//
// Created by James Pickering on 12/23/24.
//

#include <trundle/util/keyboard.hpp>

#include <ncurses.h>
#include <unordered_map>
#include <vector>

namespace trundle {

struct KeyNode {
    Key leaf = Key::None;
    std::unordered_map<int, KeyNode> branches;// turn to linked list map
};

struct KeyTree {
    KeyNode root{};
};

struct KeyboardData {
    std::unordered_map<Key, std::vector<int>> keyMap{};
    KeyTree keyTree{};
    Key currKey = Key::None;
    char currChar{};
    std::unordered_map<unsigned int, std::function<void(KeyboardEvent&)>> callbacks{};
    unsigned int nextCallbackId = 1;
};

static auto _d = KeyboardData{};

auto Keyboard::init() -> void {
    _d.keyMap[Key::CtrlA] = {1};
    _d.keyMap[Key::CtrlB] = {2};
    _d.keyMap[Key::CtrlD] = {4};
    _d.keyMap[Key::CtrlE] = {5};
    _d.keyMap[Key::CtrlF] = {6};
    _d.keyMap[Key::CtrlG] = {7};
    _d.keyMap[Key::CtrlH] = {8};
    _d.keyMap[Key::CtrlI] = {9};
    _d.keyMap[Key::CtrlK] = {11};
    _d.keyMap[Key::CtrlL] = {12};
    _d.keyMap[Key::CtrlN] = {14};
    _d.keyMap[Key::CtrlP] = {16};
    _d.keyMap[Key::CtrlR] = {18};
    _d.keyMap[Key::CtrlT] = {20};
    _d.keyMap[Key::CtrlU] = {21};
    _d.keyMap[Key::CtrlW] = {23};
    _d.keyMap[Key::CtrlX] = {24};
    _d.keyMap[Key::Delete] = {127};
    _d.keyMap[Key::Down] = {27, 91, 66};
    _d.keyMap[Key::Enter] = {10};
    _d.keyMap[Key::Escape] = {27};
    _d.keyMap[Key::Left] = {27, 91, 68};
    _d.keyMap[Key::OptO] = {195, 184};
    _d.keyMap[Key::OptQ] = {197, 147};
    _d.keyMap[Key::OptR] = {194, 174};
    _d.keyMap[Key::OptS] = {195, 159};
    _d.keyMap[Key::OptLeft] = {27, 91, 49, 59, 51, 68};
    _d.keyMap[Key::OptRight] = {27, 91, 49, 59, 51, 67};
    _d.keyMap[Key::Right] = {27, 91, 67};
    _d.keyMap[Key::Tab] = {9};
    _d.keyMap[Key::ShiftTab] = {27, 91, 90};
    _d.keyMap[Key::ShiftLeft] = {27, 91, 49, 59, 50, 68};
    _d.keyMap[Key::ShiftRight] = {27, 91, 49, 59, 50, 67};
    _d.keyMap[Key::Up] = {27, 91, 65};

    KeyNode* node;
    for (const auto& [k, seq] : _d.keyMap) {
        node = &_d.keyTree.root;
        for (const auto& i : seq) {
            if (!node->branches.count(i)) {
                node->branches[i] = KeyNode{};
            }
            node = &node->branches[i];
        }
        node->leaf = k;
    }
}

auto Keyboard::poll() -> void {
    auto node = &_d.keyTree.root;
    _d.currChar = getch();
    auto c = _d.currChar;
    while (node->branches.count(c)) {
        c = static_cast<char>(c);
        node = &node->branches[c];
        c = getch();
    }
    _d.currKey = node->leaf;

    if (_d.currChar > -1) {
        auto event = KeyboardEvent{};
        for (const auto& [_, callback] : _d.callbacks) {
            callback(event);
            if (event.accepted()) {
                break;
            }
        }
    }
}

Key Keyboard::currKey() {
    return _d.currKey;
}

auto Keyboard::currChar() -> char {
    return _d.currChar;
}

auto Keyboard::addListener(std::function<void(KeyboardEvent&)>&& callback) -> unsigned int {
    _d.callbacks[_d.nextCallbackId] = callback;
    return _d.nextCallbackId++;
}

auto Keyboard::removeListener(unsigned int id) -> void {
    _d.callbacks.erase(id);
}

auto KeyboardEvent::accept() -> void {
    _accepted = true;
}

auto KeyboardEvent::accepted() const -> bool {
    return _accepted;
}

}