#pragma once


#include "../InputMode.h"
#include "Instruction.h"

class ModeChangeInstruction : public Instruction {
private:
    InputMode newMode;
public:
    explicit ModeChangeInstruction(InputMode newMode)
            : Instruction(InstructionType::CHANGE_MODE), newMode(newMode) {};

    InputMode getNewMode() const {
        return newMode;
    }
};



