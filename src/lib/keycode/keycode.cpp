#include <string>
#include "depp-keycode/src/keytable.h"

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

std::string linux_keycode_to_yaml_name(unsigned linux_keycode) {
    return linux_rawname_to_yaml_name(keycode_linux_rawname(linux_keycode));
}