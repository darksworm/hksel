#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdio>

int main(int argc, char *argv[]) {
    auto display = XOpenDisplay(nullptr);
    auto window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 100, 100, 0, 0, 0);

    XMapWindow(display, window);
    XSelectInput(display, window, KeyPressMask | ButtonPressMask | StructureNotifyMask);

    bool keep_running = true;
    XEvent event;

    while (keep_running) {
        XNextEvent(display, &event);

        switch (event.type) {
            case DestroyNotify:
            case UnmapNotify:
                keep_running = 0;
                break;
            case KeyPress: {
                printf("recv keypress\n");
                break;
            }
        }
    }

    XCloseDisplay(display);

    return 0;
}
