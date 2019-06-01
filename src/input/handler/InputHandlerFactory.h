#pragma once


#include "InputState.h"
#include "InputHandler.h"

class InputHandlerFactory {
public:
    static InputHandler *getInputHandler(InputState type);
    static bool isCorrectHandler(InputHandler *handler, InputState type);
};



