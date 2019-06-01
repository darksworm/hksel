#pragma once


#include "InputHandler.h"

class SelectionInputHandler : public InputHandler {
public:
    InputInstruction *handleKeyPress(unsigned keyPress) override;
};



