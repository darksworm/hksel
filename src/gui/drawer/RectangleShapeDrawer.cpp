#include "RectangleShapeDrawer.h"

Shape RectangleShapeDrawer::calcNextShape(ShapeProperties properties, Hotkey *hotkey, bool selected, long index) {
    return Shape();
}

Shape RectangleShapeDrawer::drawNextShape(ShapeProperties shapeProperties, Shape shape) {
    XPoint *pos = getNextShapePosition(shapeProperties);

    XDrawRectangle(windowManager->getDisplay(), windowManager->getWindow(), graphicsContext, pos->x, pos->y,
                   shapeProperties.width, shapeProperties.height);

    // TODO: these are probably unnecessary ...
    shape.height = shapeProperties.width;
    shape.width = shapeProperties.height;

    lastShapePosition = pos;
    return shape;
}

XPoint *RectangleShapeDrawer::getNextShapePosition(ShapeProperties shapeProperties) {
    XPoint *lastShapePosition = this->lastShapePosition;
    XPoint *newShapePosition;

    if (!lastShapePosition) {
        newShapePosition = new XPoint{
                .x = (short) shapeProperties.xMargin,
                .y = (short) shapeProperties.yMargin
        };
    } else {
        // TODO: this is temporary positioning
        newShapePosition = new XPoint{
                .x = (short) (lastShapePosition->x + shapeProperties.width + shapeProperties.xMargin),
                .y = (short) shapeProperties.yMargin
        };
    }

    return newShapePosition;
}

ShapeProperties RectangleShapeDrawer::calcShapeProps(Window window) {
    // TODO: calculate dynamically
    ShapeProperties shapeProperties{
            .width = 220,
            .height = 120,
            .xMargin = 10,
            .yMargin = 10,
            .rows = 4,
            .columns = 4,
    };

    return shapeProperties;
}
