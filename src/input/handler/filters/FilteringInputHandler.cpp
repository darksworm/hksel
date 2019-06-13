#include <linux/input-event-codes.h>
#include "FilteringInputHandler.h"
#include "../instruction/FilterInstruction.h"

Instruction *FilteringInputHandler::handleKeyPress(unsigned keyPress) {
    auto instruction = InputHandler::handleKeyPress(keyPress);

    switch (instruction->getType()) {
        case InstructionType::EXIT: {
            this->buffer.clear();

            delete instruction;

            instruction = new Instruction(InstructionType::NONE);
        }

        case InstructionType::NONE: {
            if (shouldAddToBuffer(keyPress)) {
                this->buffer.push_back(keyPress);

                delete instruction;

                instruction = new FilterInstruction(this->getFilter());
            }

            break;
        }
        default: break;
    }

    return instruction;
}

