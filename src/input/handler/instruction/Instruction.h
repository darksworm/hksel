#pragma once


#include "InstructionType.h"

class Instruction {
public:
    explicit Instruction(const InstructionType &type) : type(type) {};

    InstructionType getType() {
        return type;
    };

    virtual ~Instruction() {};

private:
    InstructionType type;
};



