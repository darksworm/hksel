

#include "InputHandlerFactory.h"
#include "SelectionInputHandler.h"
#include "filters/TextFilteringInputHandler.h"
#include "filters/KeyFilteringInputHandler.h"

InputHandler *InputHandlerFactory::getInputHandler(InputState type) {
    switch (type) {
        case InputState::KEY_FILTER:
            return new KeyFilteringInputHandler();
        case InputState::TEXT_FILTER:
            return new TextFilteringInputHandler();
        case InputState::SELECTION:
            return new SelectionInputHandler();
    }
}

bool InputHandlerFactory::isCorrectHandler(InputHandler *handler, InputState type) {
    if (handler == nullptr) {
        return false;
    }

    if (type == InputState::SELECTION && dynamic_cast<SelectionInputHandler *>(handler)) {
        return true;
    }

    if (type == InputState::TEXT_FILTER && dynamic_cast<TextFilteringInputHandler *>(handler)) {
        return true;
    }

    if (type == InputState::KEY_FILTER && dynamic_cast<KeyFilteringInputHandler *>(handler)) {
        return true;
    }

    return false;
}
