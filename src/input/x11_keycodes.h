#pragma once

#include <X11/Xutil.h>
#include <linux/input-event-codes.h>

unsigned x11_keycode_to_libinput_code(KeySym key) {
    int scancode = 0;
    int code = (int) key;
    if (code >= '0' && code <= '9') {
        scancode = (code & 0xF) - 1;
        if (scancode < 0) scancode += 10;
        scancode += KEY_1;
    } else if (code >= 0xFF50 && code <= 0xFF58) {
        static const uint16_t map[] =
                {KEY_HOME, KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN,
                 KEY_PAGEUP, KEY_PAGEDOWN, KEY_END, 0};
        scancode = map[code & 0xF];
    } else if (code >= 0xFFE1 && code <= 0xFFEE) {
        static const uint16_t map[] =
                {KEY_LEFTSHIFT, KEY_LEFTSHIFT,
                 KEY_LEFTCTRL, KEY_LEFTCTRL,
                 KEY_LEFTSHIFT, KEY_CAPSLOCK,
                 0, 0,
                 KEY_LEFTALT, KEY_RIGHTALT,
                 0, 0, 0, 0};
        scancode = map[code & 0xF];
    } else if ((code >= 'A' && code <= 'Z') || (code >= 'a' && code <= 'z')) {
        static const uint16_t map[] = {
                KEY_A, KEY_B, KEY_C, KEY_D, KEY_E,
                KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
                KEY_K, KEY_L, KEY_M, KEY_N, KEY_O,
                KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
                KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z};
        scancode = map[(code & 0x5F) - 'A'];
    } else {
        switch (code) {
            case XK_space:
                scancode = KEY_SPACE;
                break;
            case XK_exclam:
                scancode = KEY_1;
                break;
            case XK_at:
                scancode = KEY_2;
                break;
            case XK_numbersign:
                scancode = KEY_3;
                break;
            case XK_dollar:
                scancode = KEY_4;
                break;
            case XK_percent:
                scancode = KEY_5;
                break;
            case XK_asciicircum:
                scancode = KEY_6;
                break;
            case XK_ampersand:
                scancode = KEY_7;
                break;
            case XK_asterisk:
                scancode = KEY_8;
                break;
            case XK_parenleft:
                scancode = KEY_9;
                break;
            case XK_parenright:
                scancode = KEY_0;
                break;
            case XK_minus:
                scancode = KEY_MINUS;
                break;
            case XK_underscore:
                scancode = KEY_MINUS;
                break;
            case XK_equal:
                scancode = KEY_EQUAL;
                break;
            case XK_plus:
                scancode = KEY_EQUAL;
                break;
            case XK_BackSpace:
                scancode = KEY_BACKSPACE;
                break;
            case XK_Tab:
                scancode = KEY_TAB;
                break;
            case XK_braceleft:
                scancode = KEY_LEFTBRACE;
                break;
            case XK_braceright:
                scancode = KEY_RIGHTBRACE;
                break;
            case XK_bracketleft:
                scancode = KEY_LEFTBRACE;
                break;
            case XK_bracketright:
                scancode = KEY_RIGHTBRACE;
                break;
            case XK_Return:
                scancode = KEY_ENTER;
                break;
            case XK_semicolon:
                scancode = KEY_SEMICOLON;
                break;
            case XK_colon:
                scancode = KEY_SEMICOLON;
                break;
            case XK_apostrophe:
                scancode = KEY_APOSTROPHE;
                break;
            case XK_quotedbl:
                scancode = KEY_APOSTROPHE;
                break;
            case XK_grave:
                scancode = KEY_GRAVE;
                break;
            case XK_asciitilde:
                scancode = KEY_GRAVE;
                break;
            case XK_backslash:
                scancode = KEY_BACKSLASH;
                break;
            case XK_bar:
                scancode = KEY_BACKSLASH;
                break;
            case XK_comma:
                scancode = KEY_COMMA;
                break;
            case XK_less:
                scancode = KEY_COMMA;
                break;
            case XK_period:
                scancode = KEY_DOT;
                break;
            case XK_greater:
                scancode = KEY_DOT;
                break;
            case XK_slash:
                scancode = KEY_SLASH;
                break;
            case XK_question:
                scancode = KEY_SLASH;
                break;
            case XK_Caps_Lock:
                scancode = KEY_CAPSLOCK;
                break;
            case XK_F1:
                scancode = KEY_F1;
                break;
            case XK_F2:
                scancode = KEY_F2;
                break;
            case XK_F3:
                scancode = KEY_F3;
                break;
            case XK_F4:
                scancode = KEY_F4;
                break;
            case XK_F5:
                scancode = KEY_F5;
                break;
            case XK_F6:
                scancode = KEY_F6;
                break;
            case XK_F7:
                scancode = KEY_F7;
                break;
            case XK_F8:
                scancode = KEY_F8;
                break;
            case XK_F9:
                scancode = KEY_F9;
                break;
            case XK_F10:
                scancode = KEY_F10;
                break;
            case XK_Num_Lock:
                scancode = KEY_NUMLOCK;
                break;
            case XK_Scroll_Lock:
                scancode = KEY_SCROLLLOCK;
                break;
            case XK_Page_Down:
                scancode = KEY_PAGEDOWN;
                break;
            case XK_Insert:
                scancode = KEY_INSERT;
                break;
            case XK_Delete:
                scancode = KEY_DELETE;
                break;
            case XK_Page_Up:
                scancode = KEY_PAGEUP;
                break;
            case XK_Escape:
                scancode = KEY_ESC;
                break;
                /// case 0x0003: scancode = KEY_CENTER; break; TODO: wtf is a key_center?
        }
    }

    return (unsigned) scancode;
}
