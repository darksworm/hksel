
#include <vector>
#include <cstring>
#include <algorithm>
#include "TextFilteringInputHandler.h"
#include "../../../lib/keycode/keycode.h"

std::string TextFilteringInputHandler::getFilterText() {
    return std::__cxx11::string();
}

InputMode TextFilteringInputHandler::getNextMode() {
    return InputMode::KEY_FILTER;
}

std::function<bool(Hotkey *)> TextFilteringInputHandler::getFilter() {
    auto bufferString = bufferToString();

    /** mom, look at me im using lambdas
     AKA refactor me please */
    return std::function<bool(Hotkey *hotkey)>(
            [bufferString](Hotkey *hotkey) {
                auto it = std::search(
                        hotkey->getDescription().begin(), hotkey->getDescription().end(),
                        bufferString.begin(), bufferString.end(),
                        [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
                );

                if (it != hotkey->getDescription().end()) {
                    return true;
                }

                it = std::search(
                        hotkey->getName().begin(), hotkey->getName().end(),
                        bufferString.begin(), bufferString.end(),
                        [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
                );

                return it != hotkey->getName().end();
            }
    );
}

Instruction *TextFilteringInputHandler::handleKeyPress(unsigned keyPress) {
    auto instruction = FilteringInputHandler::handleKeyPress(keyPress);
}

bool TextFilteringInputHandler::shouldAddToBuffer(unsigned keyPress) {
    return isTextualKey(keyPress);
}

bool TextFilteringInputHandler::isTextualKey(unsigned keyPress) {
    return strlen(keycode_linux_rawname(keyPress)) == 1;
}

std::string TextFilteringInputHandler::bufferToString() {
    std::string bufferString;

    for (auto &&keyPress: buffer) {
        bufferString.push_back(*keycode_linux_rawname(keyPress));
    }

    return bufferString;
}
