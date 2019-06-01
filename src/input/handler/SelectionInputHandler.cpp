

#include <linux/input-event-codes.h>
#include "SelectionInputHandler.h"
#include "../../gui/HotkeyPickerDrawer.h"
#include "instruction/MoveInputInstruction.h"

InputInstruction *SelectionInputHandler::handleKeyPress(unsigned keyPress) {
    auto instruction = InputHandler::handleKeyPress(keyPress);

    if (instruction->getInputInstruction() == InputInstructionType::NONE) {
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
            instruction = new MoveInputInstruction(move);
        }
    }

    return instruction;
}
