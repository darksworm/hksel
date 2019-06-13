

#include "KeyFilteringInputHandler.h"

std::string KeyFilteringInputHandler::getFilterText() {
    return std::__cxx11::string();
}


InputMode KeyFilteringInputHandler::getNextMode() {
    return InputMode::SELECTION;
}

std::function<bool(Hotkey *)> KeyFilteringInputHandler::getFilter() {
    return std::function<bool(Hotkey *)>();
}

bool KeyFilteringInputHandler::shouldAddToBuffer(unsigned keyPress) {
    return true;
}
