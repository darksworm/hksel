#pragma once


#include "FilteringInputHandler.h"

class KeyFilteringInputHandler : public FilteringInputHandler {
public:
    std::string getFilterText() override;

    std::function<bool(Hotkey *)> getFilter() override;

    InputMode getNextMode() override;

protected:
    bool shouldAddToBuffer(unsigned keyPress) override;
};



