
#include "Instruction.h"
#include "../../../gui/HotkeyPickerDrawer.h"

class MoveInstruction : public Instruction {
private:
    HotkeyPickerMove moveDirection;
public:
    HotkeyPickerMove getMoveDirection() {
        return this->moveDirection;
    }

    explicit MoveInstruction(HotkeyPickerMove moveDirection) : Instruction(InstructionType::MOVE),
                                                                    moveDirection(moveDirection) {}
};