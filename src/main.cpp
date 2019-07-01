#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml-cpp/yaml.h>
#include <thread>
#include <termcap.h>

#include "gui/WindowManager.h"
#include "input/KeyboardManager.h"
#include "lib/keycode/keycode.h"
#include "hotkey/hotkeyloader_yaml.h"
#include "gui/drawer/ShapeDrawerFactory.h"
#include "gui/HotkeyPickerDrawer.h"

#include "input/x11_keycodes.h"
#include "input/handler/InputMode.h"
#include "input/handler/InputHandler.h"
#include "input/handler/InputHandlerFactory.h"
#include "input/handler/instruction/MoveInstruction.h"
#include "input/handler/instruction/ModeChangeInstruction.h"
#include "input/handler/instruction/FilterInstruction.h"

#define CONSUME_KB false
#define DEBUG true


void drawText(WindowManager *windowManager, const std::string &text, Dimensions position) {
    auto display = windowManager->getDisplay();
    auto window = windowManager->getWindow();

    // TODO: these should be config options
    int screen_num = DefaultScreen(display);

    GC gc = XCreateGC(display, window, 0, nullptr);

    XSetForeground(display, gc, WhitePixel(display, screen_num));
    XSetBackground(display, gc, BlackPixel(display, screen_num));

    XDrawString(
            windowManager->getDisplay(),
            windowManager->getWindow(),
            gc,
            (int) position.x,
            (int) position.y,
            text.c_str(),
            (int) text.length()
    );

    XFreeGC(display, gc);
}

int main(int argc, char *argv[]) {
    std::vector<Hotkey> hotkeys;

    // TODO: config manager?
    load_hotkeys_dir("../static/conf.d/", &hotkeys);

    std::unique_ptr<WindowManager> windowManager(new WindowManager());
    std::unique_ptr<KeyboardManager> keyboardManager(new KeyboardManager());
    std::unique_ptr<HotkeyPickerDrawer> hotkeyPickerDrawer(
            new HotkeyPickerDrawer(windowManager.get(), ShapeType::RECTANGLE, &hotkeys));

    Display *display = windowManager->getDisplay();
    Window window = windowManager->getWindow();

    if (CONSUME_KB && !keyboardManager->openKeyboard()) {
        printf("Couldn't open keyboard");
        exit(1);
    }

    InputMode state = InputMode::SELECTION;
    int keep_running = 1;
    XEvent event;

    XSelectInput(display, window, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | StructureNotifyMask);
    hotkeyPickerDrawer->drawFrame(&*hotkeys.begin());

    std::unique_ptr<InputHandler> inputHandler(nullptr);

    unsigned eventType = 0;

    while (keep_running) {
        unsigned keyCode = 0;

        // read xevents
        while (XPending(display)) {
            XNextEvent(display, &event);

            switch (event.type) {
                case DestroyNotify:
                case UnmapNotify:
                    keep_running = 0;
                    break;

                case KeyPress: {
                    if (CONSUME_KB) {
                        break;
                    }
                    eventType = KeyPress;
                    keyCode = x11_keycode_to_libinput_code(XLookupKeysym(&event.xkey, 0));
                    break;
                }

                case KeyRelease:
                    if (CONSUME_KB) {
                        break;
                    }
                    eventType = KeyRelease;
                    keyCode = x11_keycode_to_libinput_code(XLookupKeysym(&event.xkey, 0));
                    break;

                case ConfigureNotify:
                    XClearWindow(windowManager->getDisplay(), windowManager->getWindow());
                    auto hk = hotkeyPickerDrawer->getSelectedHotkey() ? hotkeyPickerDrawer->getSelectedHotkey()
                                                                      : &*hotkeys.begin();
                    hotkeyPickerDrawer->drawFrame(hk);
                    break;
            }
        }

        if (CONSUME_KB) {
            // todo: handle exception
            keyCode = (unsigned) keyboardManager->readKeypress();
        }

        /*
        * TODO: this probably shouldn't be a static value
        *   we should probably calculate how much time has passed between cycles
        *   and sleep for (16.6ms - passed time)
        */
        std::this_thread::sleep_for(std::chrono::nanoseconds(16600000));

        if (keyCode == 0) {
            continue;
        }

        if (!InputHandlerFactory::isCorrectHandler(inputHandler.get(), state)) {
            inputHandler.reset(InputHandlerFactory::getInputHandler(state));
        }

        printf("RAW: %s FORMATTED: %s %u\n", keycode_linux_rawname(keyCode),
               keycode_linux_name(keycode_linux_to_hid(keyCode)), keyCode);

        std::unique_ptr<Instruction> instruction;

        if (eventType == KeyPress) {
            instruction = std::unique_ptr<Instruction>(inputHandler->handleKeyPress(keyCode));
        } else {
            instruction = std::unique_ptr<Instruction>(inputHandler->handleKeyRelease(keyCode));
        }

        if (instruction->getType() == InstructionType::NONE) {
            continue;
        }

        if (instruction->getType() == InstructionType::EXIT) {
            keep_running = 0;
            continue;
        }

        if (dynamic_cast<MoveInstruction *>(instruction.get())) {
            auto moveInstruction = ((MoveInstruction *) instruction.get());
            auto move = moveInstruction->getMoveDirection();

            bool moved = false;

            XClearWindow(windowManager->getDisplay(), windowManager->getWindow());

            if (move != HotkeyPickerMove::NONE) {
                moved = hotkeyPickerDrawer->move(moveInstruction->getMoveDirection(), moveInstruction->getMoveSteps());
            }

            if (move == HotkeyPickerMove::NONE || !moved) {
                hotkeyPickerDrawer->drawFrame(hotkeyPickerDrawer->getSelectedHotkey());
            }
        } else if (dynamic_cast<ModeChangeInstruction *>(instruction.get())) {
            state = ((ModeChangeInstruction *) (instruction.get()))->getNewMode();

            hotkeyPickerDrawer->setFilter(nullptr);
            XClearWindow(windowManager->getDisplay(), windowManager->getWindow());
            hotkeyPickerDrawer->drawFrame(nullptr);
        } else if (dynamic_cast<FilterInstruction *>(instruction.get())) {
            auto filterInstruction = ((FilterInstruction *) instruction.get());

            hotkeyPickerDrawer->setFilter(filterInstruction->getFilter());
            XClearWindow(windowManager->getDisplay(), windowManager->getWindow());
            hotkeyPickerDrawer->drawFrame(nullptr);

#if DEBUG
            XClearArea(
                    windowManager->getDisplay(),
                    windowManager->getWindow(),
                    500,
                    50,
                    300,
                    100,
                    false
            );

            drawText(windowManager.get(), "QUERY: " + filterInstruction->getFilterString(), Dimensions(500, 100));
#endif
        }

#if DEBUG
        XClearArea(
                windowManager->getDisplay(),
                windowManager->getWindow(),
                50,
                50,
                300,
                100,
                false
        );

        static const char *inputModes[] = {"SELECTION", "KEY_FILTER", "TEXT_FILTER"};
        drawText(windowManager.get(), inputModes[(int) state], Dimensions(100, 100));
#endif
    }

    if (CONSUME_KB) {
        keyboardManager->closeKeyboard();
    }
    windowManager->destroyWindow();

    return 0;
}
