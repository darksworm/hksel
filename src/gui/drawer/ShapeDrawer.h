#pragma once

#include "../Shape.h"
#include "../WindowManager.h"
#include <climits>

class ShapeDrawer {
    friend class HotkeyPickerDrawer;

private:
    GC createShapeGC(WindowManager *windowManager) {
        auto display = windowManager->getDisplay();
        auto window = windowManager->getWindow();

        // TODO: these should be config options
        int screen_num = DefaultScreen(display);
        unsigned int line_width = 2;
        int line_style = LineSolid;
        int cap_style = CapButt;
        int join_style = JoinBevel;

        GC gc = XCreateGC(display, window, 0, nullptr);

        XSetForeground(display, gc, WhitePixel(display, screen_num));
        XSetBackground(display, gc, BlackPixel(display, screen_num));

        XSetLineAttributes(display, gc,
                           line_width, line_style, cap_style, join_style);
        XSetFillStyle(display, gc, FillSolid);

        return gc;
    }

    GC createSelectedShapeGC(WindowManager *windowManager) {
         auto display = windowManager->getDisplay();
        auto window = windowManager->getWindow();

        // TODO: these should be config options
        int screen_num = DefaultScreen(display);
        unsigned int line_width = 2;
        int line_style = LineSolid;
        int cap_style = CapButt;
        int join_style = JoinBevel;

        GC gc = XCreateGC(display, window, 0, nullptr);

        XColor color;
        color.red = USHRT_MAX;
        color.green = 0;
        color.blue = 0;

        color.flags = DoRed | DoGreen | DoBlue;
        XAllocColor(display, DefaultColormap(display, screen_num), &color);

        XSetForeground(display, gc, color.pixel);
        XSetBackground(display, gc, BlackPixel(display, screen_num));

        XSetLineAttributes(display, gc,
                           line_width, line_style, cap_style, join_style);
        XSetFillStyle(display, gc, FillSolid);

        return gc;
    }

protected:
    GC shapeGC;
    GC selectedShapeGC;

    WindowManager *windowManager;
    XPoint *lastShapePosition = nullptr;

    virtual Shape calcNextShape(ShapeProperties properties, Hotkey *hotkey, bool selected, long index) = 0;

    virtual Shape drawNextShape(ShapeProperties shapeProperties, Shape shape) = 0;

    virtual ShapeProperties calcShapeProps(Window window) = 0;

    virtual XPoint *getNextShapePosition(ShapeProperties shapeProperties) = 0;

public:
    ShapeDrawer(WindowManager *windowManager) {
        shapeGC = createShapeGC(windowManager);
        selectedShapeGC = createSelectedShapeGC(windowManager);

        this->windowManager = windowManager;
    }
};
