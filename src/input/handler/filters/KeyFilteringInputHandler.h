#pragma once


#include "FilteringInputHandler.h"

class KeyFilteringInputHandler : public FilteringInputHandler {
public:
    std::string getFilterText() override;

    bool isHotkeyVisible(Hotkey hotkey) override;
};



