
#include "InputInstruction.h"
#include "../../../gui/HotkeyPickerDrawer.h"

class MoveInputInstruction : public InputInstruction {
private:
    HotkeyPickerMove moveDirection;
public:
    HotkeyPickerMove getMoveDirection() {
        return this->moveDirection;
    }

    explicit MoveInputInstruction(HotkeyPickerMove moveDirection) : InputInstruction(InputInstructionType::MOVE),
                                                                    moveDirection(moveDirection) {}
};