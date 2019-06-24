#include <linux/input-event-codes.h>
#include "InputHandler.h"
#include "instruction/ModeChangeInstruction.h"
#include "SelectionInputHandler.h"
#include "filters/TextFilteringInputHandler.h"
#include "../../lib/keycode/keycode.h"

Instruction *InputHandler::handleKeyPress(unsigned keyCode) {
    if (keyCode == KEY_ESC) {
        return new Instruction(InstructionType::EXIT);
    }

    if (keyCode == KEY_CAPSLOCK) {
        InputMode mode = getNextMode();

        return new ModeChangeInstruction(mode);
    }

    if (isModifier(keyCode)) {
        addModifier(keyCode);
    }

    return new Instruction(InstructionType::NONE);
}

Instruction *InputHandler::handleKeyRelease(unsigned keyCode) {
    if (isModifier(keyCode)) {
        removeModifier(keyCode);
    }

    return new Instruction(InstructionType::NONE);
}

void InputHandler::removeModifier(unsigned keyCode) {
    activeModifiers.erase(keyCodeToYAMLName(keyCode));
}

bool InputHandler::isModifier(unsigned keyCode) {
    switch (keyCode) {
        case KEY_RIGHTSHIFT:
        case KEY_LEFTSHIFT:
            return true;
    }

    return false;
}

void InputHandler::addModifier(unsigned keyCode) {
    activeModifiers.insert(keyCodeToYAMLName(keyCode));
}

bool InputHandler::isModifierActive(std::string keyName) {
    return activeModifiers.find(keyName) != activeModifiers.end();
}

/* TODO : this should be moved to another service or something as it is
 * a duplicate of linux_rawname_to_yaml_name defined in KeyFilteringInputHandler */
std::string InputHandler::keyCodeToYAMLName(unsigned keyCode) {
    std::string linux_rawname = keycode_linux_rawname(keyCode);

    if (linux_rawname.rfind("LEFT", 0) == 0) {
        linux_rawname = linux_rawname.substr(4, std::string::npos);
    } else if (linux_rawname.rfind("RIGHT", 0) == 0) {
        linux_rawname = linux_rawname.substr(5, std::string::npos);
    }

    if (linux_rawname == "CTRL") {
        linux_rawname = "CONTROL";
    }

    return linux_rawname;
}
