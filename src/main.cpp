#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml-cpp/yaml.h>

#include "windowmanager.h"
#include "keyboardmanager.h"
#include "lib/keycode/keycode.h"

int main(int argc, char *argv[]) {
    auto *windowManager = new WindowManager();
    auto *keyboardManager = new KeyboardManager();

    Display *display = windowManager->getDisplay();
    Window window = windowManager->getWindow();

    if (!keyboardManager->openKeyboard()) {
        printf("Couldn't open keyboard");
    }

    int keep_running = 1;
    XEvent event;

    while (keep_running) {
        // read xevents
        while (XPending(display)) {
            XNextEvent(display, &event);
            switch (event.type) {
                case ClientMessage:
                    if (event.xclient.message_type == XInternAtom(display, "WM_PROTOCOLS", 1) &&
                        (Atom) event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", 1))
                        keep_running = 0;
                    break;
                    // Manage events...
                default:
                    break;
            }
        }


        // todo: handle exception
        auto keyCode = (unsigned) keyboardManager->readKeypress();

        if (keyCode == 0) {
            continue;
        }

        printf("RAW: %s FORMATTED: %s\n", keycode_linux_rawname(keyCode), keycode_linux_name(keycode_linux_to_hid(keyCode)));

        // exit the loop if exit button is pressed
        if (keyCode == 1) {
            keep_running = 0;
        }
    }

    keyboardManager->closeKeyboard();
    windowManager->destroyWindow();

    return 0;
}
