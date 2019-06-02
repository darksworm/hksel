#pragma once


#include "FilteringInputHandler.h"

class TextFilteringInputHandler : public FilteringInputHandler {
public:
    std::string getFilterText() override;

    bool isHotkeyVisible(Hotkey hotkey) override;

    InputMode getNextMode() override;
};



