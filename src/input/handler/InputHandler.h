#pragma once

#include <string>
#include "../../hotkey/hotkey.h"
#include "instruction/Instruction.h"
#include "InputMode.h"

class InputHandler {
public:
    virtual Instruction *handleKeyPress(unsigned keyPress);
    virtual InputMode getNextMode() = 0;
};