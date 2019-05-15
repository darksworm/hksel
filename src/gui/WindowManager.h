#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>

class WindowManager {
private:
    Screen* getScreen();

    void setWindowSettings();
    void newWindow();

    Display* display = nullptr;
    Window window;
public:
    Window getWindow();
    Display* getDisplay();
    void destroyWindow();
};
