#pragma once


#include "InputMode.h"
#include "InputHandler.h"

class InputHandlerFactory {
public:
    static InputHandler *getInputHandler(InputMode type);
    static bool isCorrectHandler(InputHandler *handler, InputMode type);
};



