

#include "KeyFilteringInputHandler.h"

std::string KeyFilteringInputHandler::getFilterText() {
    return std::__cxx11::string();
}

bool KeyFilteringInputHandler::isHotkeyVisible(Hotkey hotkey) {
    return false;
}

InputMode KeyFilteringInputHandler::getNextMode() {
    return InputMode::SELECTION;
}
