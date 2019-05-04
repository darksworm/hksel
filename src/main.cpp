#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    Display *display = XOpenDisplay(NULL);

    Screen *scrn = DefaultScreenOfDisplay(display);

    int height = scrn->height;
    int width = scrn->width;

    XVisualInfo vinfo;
    XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &vinfo);

    XSetWindowAttributes attr;
    attr.colormap = XCreateColormap(display, DefaultRootWindow(display), vinfo.visual, AllocNone);
    attr.border_pixel = 0;
    attr.background_pixel = 0;

    Window win = XCreateWindow(display, DefaultRootWindow(display), 0, 0, width, height, 0, vinfo.depth, InputOutput,
                               vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel | FocusChangeMask, &attr);

    XSelectInput(display, win, StructureNotifyMask);

    GC gc = XCreateGC(display, win, 0, 0);

    Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(display, win, &wm_delete_window, 1);

    XMapWindow(display, win);

    struct input_event ev[64];
    int fevdev = -1;
    int result = 0;
    int size = sizeof(struct input_event);
    int rd;
    int value;
    char name[256] = "Unknown";
    char *device = "/dev/input/event24";

    fevdev = open(device, O_RDONLY);
    if (fevdev == -1) {
        printf("Failed to open event device.\n");
        exit(1);
    }

    result = ioctl(fevdev, EVIOCGNAME(sizeof(name)), name);
    printf("Reading From : %s (%s)\n", device, name);

    printf("Getting exclusive access: ");
    result = ioctl(fevdev, EVIOCGRAB, 1);
    printf("%s\n", (result == 0) ? "SUCCESS" : "FAILURE");

    int keep_running = 1;
    XEvent event;

    while (keep_running) {
        // read xevents
        while (XPending(display)) {
            XNextEvent(display, &event);
            switch (event.type) {
                case ClientMessage:
                    if (event.xclient.message_type == XInternAtom(display, "WM_PROTOCOLS", 1) &&
                        (Atom) event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", 1))
                        keep_running = 0;
                    break;
                    // Manage events...
                default:
                    break;
            }
        }

        if ((rd = read(fevdev, ev, size * 64)) < size) {
            break;
        }

        value = ev[0].value;

        if (value != ' ' && ev[1].value == 1 && ev[1].type == 1) {
            printf("Code[%d]\n", (ev[1].code));
        }

        // exit the loop if exit button is pressed
        if (ev[1].code == 1) {
            break;
        }
    }

    // close grabbed keyboard
    ioctl(fevdev, EVIOCGRAB, 1);
    close(fevdev);

    XDestroyWindow(display, win);
    XCloseDisplay(display);
    return 0;
}
