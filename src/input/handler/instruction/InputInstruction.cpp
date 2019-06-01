

#include "InputInstruction.h"

InputInstruction::InputInstruction(const InputInstructionType &type) : type(type) {}

InputInstructionType InputInstruction::getInputInstruction() {
    return this->type;
}

InputInstruction::~InputInstruction() {

}
