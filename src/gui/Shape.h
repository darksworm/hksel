#pragma once

#include <X11/Xutil.h>
#include "../hotkey/hotkey.h"

struct ShapeProperties {
    unsigned width;
    unsigned height;

    unsigned xMargin;
    unsigned yMargin;

    unsigned rows;
    unsigned columns;
};

struct Shape {
    XPoint position;

    unsigned width;
    unsigned height;

    bool selected;
    long index;

    Hotkey *hotkey;
};

