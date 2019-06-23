
#include "Instruction.h"
#include "../../../gui/HotkeyPickerDrawer.h"

class MoveInstruction : public Instruction {
private:
    HotkeyPickerMove moveDirection;
    unsigned int moveSteps = 1;
public:
    HotkeyPickerMove getMoveDirection() {
        return this->moveDirection;
    }

    explicit MoveInstruction(HotkeyPickerMove moveDirection, unsigned int moveSteps) : Instruction(InstructionType::MOVE),
                                                                    moveDirection(moveDirection), moveSteps(moveSteps) {}

    unsigned int getMoveSteps() const {
        return moveSteps;
    }
};