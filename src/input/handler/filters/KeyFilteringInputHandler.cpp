#include <linux/input-event-codes.h>
#include "KeyFilteringInputHandler.h"
#include "../../../lib/keycode/keycode.h"

std::string KeyFilteringInputHandler::getFilterText() {
    std::string str;

    for(auto &it:buffer)
    {
        if(!str.empty())
        {
            str.append(" ");
        }

        str.append(keycode_linux_rawname(it));
    }

    return str;
}


InputMode KeyFilteringInputHandler::getNextMode() {
    return InputMode::SELECTION;
}

std::function<bool(Hotkey *)> KeyFilteringInputHandler::getFilter() {
    auto b = buffer;

    return std::function<bool(Hotkey *hotkey)>(
            [b](Hotkey *hotkey) {
//                for(auto &it : b) {
//                    auto keyStr = keycode_linux_rawname(it);
//
//                    // TODO: we need a translator from key name(from config file) to linux key name
//                    if(hotkey->getKeyCodes()->find(keyStr) != hotkey->getKeyCodes()->end())
//                    {
//                        return false;
//                    }
//                }

                return true;
            }
    );
}

bool KeyFilteringInputHandler::shouldAddToBuffer(unsigned keyPress) {
    if(keyPress == KEY_ESC)
    {
        return false;
    }

    return true;
}
