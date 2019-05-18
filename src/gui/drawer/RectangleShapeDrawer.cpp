#include "RectangleShapeDrawer.h"

Shape RectangleShapeDrawer::calcNextShape(ShapeProperties properties, Hotkey *hotkey, bool selected, long index) {
    return Shape();
}

Shape RectangleShapeDrawer::drawNextShape(ShapeProperties shapeProperties, Shape shape) {
    XPoint *pos = getNextShapePosition(shapeProperties);

    auto gc = shape.selected ? selectedShapeGC : shapeGC;

    XDrawRectangle(windowManager->getDisplay(), windowManager->getWindow(), gc, pos->x, pos->y,
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
        XPoint offset;

        if (lastShapePosition->x >= shapeProperties.width * shapeProperties.columns) {
            // move to next line
            offset.y = (short) (shapeProperties.height + shapeProperties.yMargin + lastShapePosition->y + shapeProperties.yMargin);
            offset.x = 0;
        } else {
            offset.x = (short) (lastShapePosition->x + shapeProperties.width + shapeProperties.xMargin);
            offset.y = (short) (lastShapePosition->y);
        }

        // TODO: this is temporary positioning
        newShapePosition = new XPoint{
                .x = (short) (shapeProperties.xMargin + offset.x),
                .y = (short) (offset.y)
        };
    }

    return newShapePosition;
}

ShapeProperties RectangleShapeDrawer::calcShapeProps(Window window) {
    // TODO: calculate dynamically
    ShapeProperties shapeProperties{
            .width = 220,
            .height = 120,
            .xMargin = 20,
            .yMargin = 20,
            .rows = 4,
            .columns = 4,
    };

    return shapeProperties;
}
