#include "examples/drum_machine/drum_machine.hpp"
#include "examples/file_browser/file_browser.hpp"
#include "examples/text_editor/simple_text_editor.hpp"

#include <iostream>

#include <ostream>
#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/widget/action_bar_widget.hpp>

using namespace trundle;

auto keyboardTester() -> void {
    Trundle::init();

    while (true) {
        auto c = Trundle::currChar();
        if (c >= 0) {
            Trundle::print(std::to_wstring(c));
            Trundle::print(std::wstring{L", "});
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

    int n = 1;
    // little endian if true
    if(*(char *)&n == 1) {
        std::cout << "Little Endian" << std::endl;
    } else {
        std::cout << "Big Endian" << std::endl;
    }

    Trundle::init();
    Keyboard::init();

    while (true) {
        Keyboard::poll();
        if (Keyboard::currKey() == Key::Enter) {
            break;
        }
    }

    //examples::TextEditor::run();
    //examples::FileBrowser::run();
    examples::DrumMachine::run();

    return 0;
}
