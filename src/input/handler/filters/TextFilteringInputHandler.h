#pragma once


#include "FilteringInputHandler.h"

class TextFilteringInputHandler : public FilteringInputHandler {
public:
    std::string getFilterText() override;

    std::function<bool(Hotkey *)> getFilter() override;

    InputMode getNextMode() override;

    Instruction *handleKeyPress(unsigned keyPress) override;

protected:
    bool shouldAddToBuffer(unsigned keyPress) override;
    std::string bufferToString();
private:
    bool isTextualKey(unsigned keyPress);
};



