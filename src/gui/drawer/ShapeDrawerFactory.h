#pragma once

#include "RectangleShapeDrawer.h"

enum class ShapeType {
    RECTANGLE
};

class ShapeDrawerFactory {
public:
    static ShapeDrawer *getShapeDrawer(ShapeType shapeType, WindowManager *windowManager);
};

