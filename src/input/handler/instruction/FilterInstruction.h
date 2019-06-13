#include <utility>
#include <functional>

#pragma once

#include "Instruction.h"
#include "../../../hotkey/hotkey.h"

class FilterInstruction : public Instruction {
private:
    std::function<bool(Hotkey *hotkey)> filterFunc;
public:
    explicit FilterInstruction(std::function<bool(Hotkey *hotkey)> filterFunc) : Instruction(InstructionType::FILTER) {
        this->filterFunc = std::move(filterFunc);
    }

    std::function<bool(Hotkey*)> getFilter() {
        return filterFunc;
    }
};