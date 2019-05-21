#pragma once

#include "ShapeDrawer.h"

class RectangleShapeDrawer : public ShapeDrawer {
protected:
    Shape calcNextShape(ShapeProperties properties, Hotkey *hotkey, bool selected, long index) override;

    Shape drawNextShape(ShapeProperties shapeProperties, Dimensions windowDimensions, Shape shape) override;

    ShapeProperties calcShapeProps(Window window) override;

    XPoint *getNextShapePosition(ShapeProperties shapeProperties, Dimensions windowDimensions) override;

public:
    explicit RectangleShapeDrawer(WindowManager *windowManager) : ShapeDrawer(windowManager) {}
};
