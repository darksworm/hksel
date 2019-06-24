#pragma once

#include <string>
#include <set>
#include "../../hotkey/hotkey.h"
#include "instruction/Instruction.h"
#include "InputMode.h"

class InputHandler {
public:
    virtual Instruction *handleKeyPress(unsigned keyCode);
    virtual Instruction *handleKeyRelease(unsigned keyCode);
    virtual InputMode getNextMode() = 0;
protected:
    void addModifier(unsigned keyCode);
    void removeModifier(unsigned keyCode);
    bool isModifier(unsigned keyCode);

    std::string keyCodeToYAMLName(unsigned keyCode);

    bool isModifierActive(std::string keyName);

private:
    std::set<std::string> activeModifiers;
};