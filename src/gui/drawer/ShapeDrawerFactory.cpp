
#include "ShapeDrawerFactory.h"

ShapeDrawer *ShapeDrawerFactory::getShapeDrawer(ShapeType shapeType, WindowManager *windowManager) {
    switch (shapeType) {
        case ShapeType::RECTANGLE:
            return new RectangleShapeDrawer(windowManager);
        default:
            return nullptr;
    }
}
