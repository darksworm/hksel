

#include <linux/input-event-codes.h>
#include "SelectionInputHandler.h"
#include "../../gui/HotkeyPickerDrawer.h"
#include "instruction/MoveInstruction.h"

Instruction *SelectionInputHandler::handleKeyPress(unsigned keyPress) {
    auto instruction = InputHandler::handleKeyPress(keyPress);

    if (instruction->getType() == InstructionType::NONE) {
        HotkeyPickerMove move = HotkeyPickerMove::NONE;

        switch (keyPress) {
            case KEY_H:
                move = HotkeyPickerMove::LEFT;
                break;
            case KEY_L:
                move = HotkeyPickerMove::RIGHT;
                break;
            case KEY_J:
                move = HotkeyPickerMove::DOWN;
                break;
            case KEY_K:
                move = HotkeyPickerMove::UP;
                break;
            default:
                move = HotkeyPickerMove::NONE;
                break;
        }

        if (move != HotkeyPickerMove::NONE) {
            delete instruction;
            instruction = new MoveInstruction(move);
        }
    }

    return instruction;
}

InputMode SelectionInputHandler::getNextMode() {
    return InputMode::TEXT_FILTER;
}
