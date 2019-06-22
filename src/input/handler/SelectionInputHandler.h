#pragma once


#include "InputHandler.h"

class SelectionInputHandler : public InputHandler {
public:
    Instruction *handleKeyPress(unsigned keyPress) override;

    InputMode getNextMode() override;
};



