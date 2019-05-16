#pragma once

#include "../Shape.h"
#include "../WindowManager.h"

class ShapeDrawer {
    friend class HotkeyPickerDrawer;

private:
    GC createGC(WindowManager *windowManager) {
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

protected:
    GC graphicsContext;
    WindowManager *windowManager;
    XPoint *lastShapePosition = nullptr;

    virtual Shape calcNextShape(ShapeProperties properties, Hotkey *hotkey, bool selected, long index) = 0;

    virtual Shape drawNextShape(ShapeProperties shapeProperties, Shape shape) = 0;

    virtual ShapeProperties calcShapeProps(Window window) = 0;

    virtual XPoint *getNextShapePosition(ShapeProperties shapeProperties) = 0;

public:
    ShapeDrawer(WindowManager *windowManager) {
        graphicsContext = createGC(windowManager);
        this->windowManager = windowManager;
    }
};
