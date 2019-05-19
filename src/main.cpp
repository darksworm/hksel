#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml-cpp/yaml.h>
#include <thread>

#include "gui/WindowManager.h"
#include "input/KeyboardManager.h"
#include "lib/keycode/keycode.h"
#include "hotkey/hotkeyloader_yaml.h"
#include "gui/drawer/ShapeDrawerFactory.h"
#include "gui/HotkeyPickerDrawer.h"
#include "input/x11_keycodes.h"

#define CONSUME_KB false

int main(int argc, char *argv[]) {
    std::vector<Hotkey> hotkeys;

    // TODO: config manager?
    load_hotkeys_yaml((char *) "../static/sampleconfig.yaml", &hotkeys);

    auto *windowManager = new WindowManager();
    auto *keyboardManager = new KeyboardManager();
    auto hotkeyPickerDrawer = new HotkeyPickerDrawer(windowManager, ShapeType::RECTANGLE, &hotkeys);

    Display *display = windowManager->getDisplay();
    Window window = windowManager->getWindow();

    if (CONSUME_KB && !keyboardManager->openKeyboard()) {
        printf("Couldn't open keyboard");
        exit(1);
    }

    int keep_running = 1;
    XEvent event;

    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);
    hotkeyPickerDrawer->drawFrame(&*hotkeys.begin());

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
                    keyCode = x11_keycode_to_libinput_code(XLookupKeysym(&event.xkey, 0));
                    break;
                }

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

        printf("RAW: %s FORMATTED: %s %u\n", keycode_linux_rawname(keyCode),
               keycode_linux_name(keycode_linux_to_hid(keyCode)), keyCode);

        HotkeyPickerMove move = NONE;

        switch (keyCode) {
            case KEY_ESC:
                keep_running = 0;
                break;
            case KEY_H:
                move = LEFT;
                break;
            case KEY_L:
                move = RIGHT;
                break;
            case KEY_J:
                move = DOWN;
                break;
            case KEY_K:
                move = UP;
                break;
        }

        bool moved = false;

        XClearWindow(windowManager->getDisplay(), windowManager->getWindow());

        if (move != NONE) {
            moved = hotkeyPickerDrawer->move(move);
        }

        if (move == NONE || !moved) {
            hotkeyPickerDrawer->drawFrame(hotkeyPickerDrawer->getSelectedHotkey());
        }
    }

    if (CONSUME_KB) {
        keyboardManager->closeKeyboard();
    }
    windowManager->destroyWindow();

    return 0;
}
