#pragma once

#include <X11/Xutil.h>
#include <linux/input-event-codes.h>

unsigned x11_keycode_to_libinput_code(unsigned x11_code) {
    unsigned keyCode;

    switch (x11_code) {
        case XK_Escape:
            keyCode = KEY_ESC;
            break;
        case XK_h:
            keyCode = KEY_H;
            break;
        case XK_l:
            keyCode = KEY_L;
            break;
        case XK_j:
            keyCode = KEY_J;
            break;
        case XK_k:
            keyCode = KEY_K;
            break;
        default:
            keyCode = 0;
            break;
    }

    return keyCode;
}
