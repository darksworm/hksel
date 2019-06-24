

#include <linux/input-event-codes.h>
#include "SelectionInputHandler.h"
#include "../../gui/HotkeyPickerDrawer.h"
#include "instruction/MoveInstruction.h"
#include "instruction/ModeChangeInstruction.h"

Instruction *SelectionInputHandler::handleKeyPress(unsigned keyCode) {
    auto instruction = InputHandler::handleKeyPress(keyCode);

    if (instruction->getType() == InstructionType::NONE) {
        HotkeyPickerMove move = HotkeyPickerMove::NONE;

        switch (keyCode) {
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

    if (keyCode == KEY_0 && repeatNextCommand) {
        repeatNextCommandTimes = repeatNextCommandTimes * 10;
    } else if (keyCode >= KEY_1 && keyCode <= KEY_9) {
        if (repeatNextCommand) {
            repeatNextCommandTimes = repeatNextCommandTimes * 10 + (keyCode - 1);
        } else {
            repeatNextCommandTimes = keyCode - 1;
        }

        repeatNextCommand = true;
    } else if (!isModifier(keyCode) && keyCode != KEY_G) {
        repeatNextCommandTimes = 1;
        repeatNextCommand = false;
    }

    if (keyCode == KEY_G) {
        delete instruction;

        if (isModifierActive("SHIFT")) {
            if (repeatNextCommand) {
                unsigned targetLine = repeatNextCommandTimes;
                instruction = new MoveInstruction(HotkeyPickerMove::LINE, targetLine);
            } else {
                instruction = new MoveInstruction(HotkeyPickerMove::END, 1);
            }

        } else {
            instruction = new MoveInstruction(HotkeyPickerMove::HOME, 1);
        }

        repeatNextCommand = false;
        repeatNextCommandTimes = 1;
    }

    return instruction;
}

InputMode SelectionInputHandler::getNextMode() {
    return InputMode::TEXT_FILTER;
}
