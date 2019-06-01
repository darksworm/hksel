#pragma once


#include "InputInstructionType.h"

class InputInstruction {
public:
    explicit InputInstruction(const InputInstructionType &type);

    InputInstructionType getInputInstruction();

    virtual ~InputInstruction();

private:
    InputInstructionType type;
};



