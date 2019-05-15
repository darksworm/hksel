#pragma once

#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

// todo: inteface this badboy
class KeyboardManager {
private:
    int fevdev;
public:
    bool openKeyboard();
    int readKeypress();
    void closeKeyboard();
};
