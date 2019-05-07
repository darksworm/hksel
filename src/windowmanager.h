#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>

#ifndef HKSEL_WINDOWMANAGER_H
#define HKSEL_WINDOWMANAGER_H

#endif //HKSEL_WINDOWMANAGER_H

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
