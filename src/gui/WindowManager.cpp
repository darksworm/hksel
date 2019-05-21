#include "WindowManager.h"

typedef struct {
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long inputMode;
    unsigned long status;
} Hints;

unsigned long RGBA2DWORD(int iR, int iG, int iB, int iA)
{
    return ((iA * 256 + iR) * 256 + iG) * 256 + iB;
}

void WindowManager::setWindowSettings() {
    XClassHint *class_hints = XAllocClassHint();

    class_hints->res_name = "hksel";
    class_hints->res_class = "hksel";

    XStoreName(display, this->window, class_hints->res_name);
    XSetClassHint(display, this->window, class_hints);
    XFree(class_hints);

    Atom wm_delete_win = XInternAtom(display, "WM_DELETE_this->windowDOW", 0);
    XSetWMProtocols(display, this->window, &wm_delete_win, 1);

    XMapWindow(display, this->window);

    Hints hints;
    Atom property;

    hints.flags = 2; // changing this->window decorations
    hints.decorations = 0; // disabling this->window decorations

    property = XInternAtom(display, "_MOTIF_WM_HINTS", true);

    XChangeProperty(display, this->window, property, property, 32, PropModeReplace, (unsigned char *) &hints, 5);

    XMapRaised(display, this->window);

    XSelectInput(display, this->window, StructureNotifyMask);
}

Display* WindowManager::getDisplay() {
    if( this->display == nullptr )
    {
        // TODO: can there be multiple displays?
        this->display = XOpenDisplay(nullptr);
    }

    return this->display;
}

Screen* WindowManager::getScreen() {
    Display* display = this->getDisplay();

    return DefaultScreenOfDisplay(display);
}

void WindowManager::newWindow() {
    Screen* screen = this->getScreen();

    int height = screen->height;
    int width = screen->width;

    XVisualInfo vinfo;
    XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);

    XSetWindowAttributes attr;
    attr.colormap = XCreateColormap(display, DefaultRootWindow(display), vinfo.visual, AllocNone);
    attr.border_pixel = 0;
    // TODO : this should be 0 to be transparent
    attr.background_pixel = RGBA2DWORD(0, 0, 0, 115);

    // when setting y to 0, in i3 the window appears in a negative y position, 1 works tho
    this->window = XCreateWindow(display, DefaultRootWindow(display), 0, 1, (unsigned) width, (unsigned) height - 1, 0,
                               vinfo.depth, InputOutput,
                               vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel | FocusChangeMask, &attr);

    this->setWindowSettings();
}


Window WindowManager::getWindow() {
    if( !this->window )
    {
       this->newWindow();
    }

    return this->window;
}

void WindowManager::destroyWindow() {
    XDestroyWindow( this->getDisplay(), this->getWindow() );
    XCloseDisplay( this->getDisplay() );
}

void WindowManager::getWindowDimensions(unsigned int *width, unsigned int *height) {
    int empty;
    unsigned int u_empty;
    Window root;

    XGetGeometry(display, window, &root, &empty, &empty, width, height, &u_empty, &u_empty);
}
