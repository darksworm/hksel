#include <linux/input-event-codes.h>
#include "InputHandler.h"

InputInstruction *InputHandler::handleKeyPress(unsigned keyPress) {
    // TODO: handle mode switching here

    if (keyPress == KEY_ESC) {
        return new InputInstruction(InputInstructionType::EXIT);
    }

    return new InputInstruction(InputInstructionType::NONE);
}
