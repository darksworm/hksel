#pragma once

#include <X11/Xutil.h>
#include "../hotkey/hotkey.h"

struct Dimensions {
    unsigned x;
    unsigned y;
};

struct ShapeProperties {
    Dimensions dimensions;
    Dimensions margins;
    Dimensions itemCounts;

    XRectangle topTextRect;
    XRectangle midTextRect;
    XRectangle botTextRect;
};

struct Shape {
    XPoint position;

    bool selected;
    long index;

    Hotkey *hotkey;
};

