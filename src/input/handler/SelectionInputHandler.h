#pragma once


#include "InputHandler.h"

class SelectionInputHandler : public InputHandler {
public:
    Instruction *handleKeyPress(unsigned keyPress) override;

    InputMode getNextMode() override;
private:
    unsigned int repeatNextCommandTimes = 1;
    bool repeatNextCommand = false;
};



