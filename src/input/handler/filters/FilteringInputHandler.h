#pragma once

#include <functional>
#include "../InputHandler.h"

class FilteringInputHandler : public InputHandler {
public:
    virtual std::string getFilterText() = 0;
    virtual std::function<bool (Hotkey *hotkey)> getFilter() = 0;
    Instruction *handleKeyPress(unsigned keyPress) override;

protected:
    std::vector<unsigned> buffer;

    virtual bool shouldAddToBuffer(unsigned keyPress) = 0;
};
