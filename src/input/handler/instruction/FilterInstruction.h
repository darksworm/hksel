#include <utility>

#include <utility>
#include <functional>

#pragma once

#include "Instruction.h"
#include "../../../hotkey/hotkey.h"

class FilterInstruction : public Instruction {
private:
    std::function<bool(Hotkey *hotkey)> filterFunc;
    std::string filterString;
public:
    explicit FilterInstruction(std::function<bool(Hotkey *hotkey)> filterFunc, std::string filterString) : Instruction(
            InstructionType::FILTER), filterString(std::move(filterString)) {
        this->filterFunc = std::move(filterFunc);
    }

    std::function<bool(Hotkey *)> getFilter() {
        return filterFunc;
    }

    const std::string &getFilterString() const {
        return filterString;
    }
};