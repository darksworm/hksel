#pragma once

#include "../InputHandler.h"

class FilteringInputHandler : public InputHandler {
public:
    virtual std::string getFilterText() = 0;
    virtual bool isHotkeyVisible(Hotkey hotkey) = 0;
};
