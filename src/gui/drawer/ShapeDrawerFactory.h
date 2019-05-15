#pragma once

#include "RectangleShapeDrawer.h"

enum ShapeType {
    RECTANGLE
};

class ShapeDrawerFactory {
public:
    static ShapeDrawer *getShapeDrawer(ShapeType shapeType, WindowManager *windowManager);
};

