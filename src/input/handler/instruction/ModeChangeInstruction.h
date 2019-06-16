#pragma once


#include "../InputMode.h"
#include "Instruction.h"

class ModeChangeInstruction : public Instruction {
private:
    InputMode newMode;
    unsigned bufferedKeyPress;
    bool sendBuffer;
public:
    explicit ModeChangeInstruction(InputMode newMode, unsigned bufferedKeypress = 0, bool sendBuffer = false)
            : Instruction(InstructionType::CHANGE_MODE), newMode(newMode), bufferedKeyPress(bufferedKeypress),
              sendBuffer(sendBuffer) {};

    InputMode getNewMode() const {
        return newMode;
    }

    unsigned int getBufferedKeyPress() const {
        return bufferedKeyPress;
    }

    bool isSendBuffer() const {
        return sendBuffer;
    }
};



