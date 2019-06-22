#include <linux/input-event-codes.h>
#include "KeyFilteringInputHandler.h"
#include "../../../lib/keycode/keycode.h"

std::string linux_rawname_to_yaml_name(std::string linux_rawname) {
    if (linux_rawname.rfind("LEFT", 0) == 0) {
        linux_rawname = linux_rawname.substr(4, std::string::npos);
    } else if (linux_rawname.rfind("RIGHT", 0) == 0) {
        linux_rawname = linux_rawname.substr(5, std::string::npos);
    }

    if (linux_rawname == "CTRL") {
        linux_rawname = "CONTROL";
    }

    return linux_rawname;
}

std::string KeyFilteringInputHandler::getFilterText() {
    std::string str;

    for (auto &it:buffer) {
        if (!str.empty()) {
            str.append(" ");
        }

        str.append(linux_rawname_to_yaml_name(keycode_linux_rawname(it)));
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
                for (auto &it : b) {
                    std::string keyStr = keycode_linux_rawname(it);

                    keyStr = linux_rawname_to_yaml_name(keyStr);

                    // TODO: we need a translator from key name(from config file) to linux key name
                    if (hotkey->getKeyCodes()->find(keyStr) == hotkey->getKeyCodes()->end()) {
                        return false;
                    }
                }

                return true;
            }
    );
}

bool KeyFilteringInputHandler::shouldAddToBuffer(unsigned keyPress) {
    if (keyPress == KEY_ESC) {
        return false;
    }

    return true;
}

