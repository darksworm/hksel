#include <linux/input-event-codes.h>
#include "InputHandler.h"
#include "instruction/ModeChangeInstruction.h"
#include "SelectionInputHandler.h"
#include "filters/TextFilteringInputHandler.h"

Instruction *InputHandler::handleKeyPress(unsigned keyPress) {
    // TODO: handle mode switching here

    if (keyPress == KEY_ESC) {
        return new Instruction(InstructionType::EXIT);
    }

    if (keyPress == KEY_CAPSLOCK) {
        InputMode mode = getNextMode();

        return new ModeChangeInstruction(mode);
    }

    return new Instruction(InstructionType::NONE);
}
