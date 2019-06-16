
#include <vector>
#include <cstring>
#include <algorithm>
#include <linux/input-event-codes.h>
#include "TextFilteringInputHandler.h"
#include "../../../lib/keycode/keycode.h"
#include "../instruction/FilterInstruction.h"

std::string TextFilteringInputHandler::getFilterText() {
    return this->bufferToString();
}

InputMode TextFilteringInputHandler::getNextMode() {
    return InputMode::KEY_FILTER;
}

std::function<bool(Hotkey *)> TextFilteringInputHandler::getFilter() {
    auto bufferString = bufferToString();

    auto upperCase = [](std::string input) {
        for (char &it : input)
            it = static_cast<char>(toupper((unsigned char) it));
        return input;
    };

    /** mom, look at me im using lambdas
     AKA refactor me please */
    return std::function<bool(Hotkey *hotkey)>(
            [bufferString, upperCase](Hotkey *hotkey) {
                auto str = upperCase(bufferString);

                if (upperCase(hotkey->getDescription()).find(str) != std::string::npos) {
                    return true;
                }

                return upperCase(hotkey->getDescription()).find(str) != std::string::npos;
            }
    );
}

Instruction *TextFilteringInputHandler::handleKeyPress(unsigned keyPress) {
    switch (keyPress) {
        case KEY_BACKSPACE: {
            if (!this->buffer.empty()) {
                this->buffer.pop_back();
            }

            return new FilterInstruction(this->getFilter(), this->getFilterText());
        }

        case KEY_DELETE: {
            this->buffer.clear();

            return new FilterInstruction(this->getFilter(), this->getFilterText());
        }

        default:
            return FilteringInputHandler::handleKeyPress(keyPress);
    }

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
