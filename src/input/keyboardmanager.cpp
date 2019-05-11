#include "keyboardmanager.h"

void KeyboardManager::closeKeyboard() {
    ioctl(fevdev, EVIOCGRAB, 1);
    close(fevdev);
}

int KeyboardManager::readKeypress() {
    int size = sizeof(struct input_event);
    int rd;
    int value;
    struct input_event ev[64];

    if ((rd = read(fevdev, ev, size * 64)) < size) {
        throw NULL;
    }

    value = ev[0].value;
    if (value != ' ' && ev[1].value == 1 && ev[1].type == 1) {

        return ev[1].code;
    }

    // TODO: wtf is this empty return value?
    return 0;
    // TODO: after this exits a ton of newlines are dumped
}

bool KeyboardManager::openKeyboard() {
    // sleep for 100ms before opening keyboard, otherwise key spam might occur
    // after the application is closed - https://stackoverflow.com/questions/41995349
    usleep(100000);

    int result = 0;

    char name[256] = "Unknown";
    // TODO: get device dynamically
    // FOR NOW checking evtest
    char *device = "/dev/input/event5";

    fevdev = open(device, O_RDONLY);
    if (fevdev == -1) {
        //printf("Failed to open event device.\n");
        return false;
    }

    result = ioctl(fevdev, EVIOCGNAME(sizeof(name)), name);
    //printf("Reading From : %s (%s)\n", device, name);

    result = ioctl(fevdev, EVIOCGRAB, 1);

    return result == 0;
}
