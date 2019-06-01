#pragma once

#include <string>
#include "../../hotkey/hotkey.h"
#include "instruction/InputInstruction.h"

class InputHandler {
public:
    virtual InputInstruction *handleKeyPress(unsigned keyPress);
};