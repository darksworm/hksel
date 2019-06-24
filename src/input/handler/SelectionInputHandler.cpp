

#include <linux/input-event-codes.h>
#include "SelectionInputHandler.h"
#include "../../gui/HotkeyPickerDrawer.h"
#include "instruction/MoveInstruction.h"
#include "instruction/ModeChangeInstruction.h"

Instruction *SelectionInputHandler::handleKeyPress(unsigned keyPress) {
    auto instruction = InputHandler::handleKeyPress(keyPress);

    if (instruction->getType() == InstructionType::NONE) {
        HotkeyPickerMove move = HotkeyPickerMove::NONE;

        switch (keyPress) {
            case KEY_SLASH:
                delete instruction;
                instruction = new ModeChangeInstruction(InputMode::TEXT_FILTER);
                break;
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
            instruction = new MoveInstruction(move, repeatNextCommandTimes);
        }
    }

    if (keyPress == KEY_0 && repeatNextCommand) {
        repeatNextCommandTimes = repeatNextCommandTimes * 10;
    } else if (keyPress >= KEY_1 && keyPress <= KEY_9) {
        if (repeatNextCommand) {
            repeatNextCommandTimes = repeatNextCommandTimes * 10 + (keyPress - 1);
        } else {
            repeatNextCommandTimes = keyPress - 1;
        }

        repeatNextCommand = true;
    } else {
        repeatNextCommandTimes = 1;
        repeatNextCommand = false;
    }

    if(keyPress == KEY_G && isModifierActive("SHIFT"))
    {
        repeatNextCommand = false;
        repeatNextCommandTimes = 1;

        delete instruction;
        instruction = new MoveInstruction(HotkeyPickerMove::END, 1);
    }

    return instruction;
}

InputMode SelectionInputHandler::getNextMode() {
    return InputMode::TEXT_FILTER;
}
