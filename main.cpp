#include "examples/file_browser/file_browser.hpp"
#include "examples/text_editor/simple_text_editor.hpp"

#include <trundle/trundle.hpp>
#include <trundle/util/keyboard.hpp>
#include <trundle/widget/action_bar_widget.hpp>

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

    Trundle::init();
    Keyboard::init();

    while (true) {
        Keyboard::poll();
        if (Keyboard::currKey() == Key::Enter) {
            break;
        }
    }

    //examples::SimpleTextEditor::run();
    examples::FileBrowser::run();

    return 0;
}
