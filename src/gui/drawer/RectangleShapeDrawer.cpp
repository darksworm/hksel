#include "RectangleShapeDrawer.h"

Shape RectangleShapeDrawer::calcNextShape(ShapeProperties properties, Hotkey *hotkey, bool selected, long index) {
    return Shape();
}

Shape RectangleShapeDrawer::drawNextShape(ShapeProperties shapeProperties, Dimensions windowDimensions, Shape shape) {
    XPoint *pos = getNextShapePosition(shapeProperties, windowDimensions);

    auto gc = shape.selected ? selectedShapeGC : shapeGC;

    XDrawRectangle(windowManager->getDisplay(), windowManager->getWindow(), gc, pos->x, pos->y,
                   shapeProperties.dimensions.x, shapeProperties.dimensions.y);

    shape.position = *pos;

    drawText(shapeProperties, shape);

    lastShapePosition = pos;
    return shape;
}

XPoint *RectangleShapeDrawer::getNextShapePosition(ShapeProperties shapeProperties, Dimensions windowDimensions) {
    XPoint *lastShapePosition = this->lastShapePosition;
    XPoint *newShapePosition;

    unsigned int xCenterMargin;
    unsigned int line_width = shapeProperties.dimensions.x * shapeProperties.itemCounts.x +
                              (shapeProperties.margins.x * shapeProperties.itemCounts.x - 1);

    xCenterMargin = (windowDimensions.x - line_width) / 2;

    if (!lastShapePosition) {
        newShapePosition = new XPoint{
                .x = (short) xCenterMargin,
                .y = (short) shapeProperties.margins.y
        };
    } else {
        XPoint offset;

        if (lastShapePosition->x >= shapeProperties.dimensions.x * (shapeProperties.itemCounts.x - 1) + xCenterMargin) {
            // move to next line
            offset.y = (short) (shapeProperties.dimensions.y + shapeProperties.margins.y + lastShapePosition->y +
                                shapeProperties.margins.y);
            offset.x = (short) xCenterMargin;
        } else {
            offset.x = (short) (lastShapePosition->x + shapeProperties.dimensions.x + shapeProperties.margins.x);
            offset.y = (short) (lastShapePosition->y);
        }

        // TODO: this is temporary positioning
        newShapePosition = new XPoint{
                .x = (short) (offset.x),
                .y = (short) (offset.y)
        };
    }

    return newShapePosition;
}

ShapeProperties RectangleShapeDrawer::calcShapeProps(Window window) {
    // TODO: calculate dynamically
    ShapeProperties shapeProperties{
            .dimensions = Dimensions{
                    .x = 300,
                    .y = 150,
            },
            .margins = Dimensions{
                    .x = 20,
                    .y = 20,
            },
            .itemCounts = Dimensions{
                    .x = 4,
                    .y = 4,
            },
            .topTextRect = XRectangle{
                    .x = 10,
                    .y = 20,
                    .width = (unsigned short) (shapeProperties.dimensions.x - 10),
                    .height = 40
            },
            .midTextRect = XRectangle{
                    .x = shapeProperties.topTextRect.x,
                    .y = (short) (shapeProperties.dimensions.y - 80),
                    .width = shapeProperties.topTextRect.width,
                    .height = shapeProperties.topTextRect.height
            },
            .botTextRect = XRectangle{
                    .x = shapeProperties.topTextRect.x,
                    .y = (short) (shapeProperties.dimensions.y - 40),
                    .width = shapeProperties.topTextRect.width,
                    .height = shapeProperties.topTextRect.height
            }
    };

    return shapeProperties;
}
