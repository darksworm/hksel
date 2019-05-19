#include "HotkeyPickerDrawer.h"
#include "../exceptions/OutOfBounds.h"

HotkeyPickerDrawer::HotkeyPickerDrawer(WindowManager *windowManager, ShapeType shapeType,
                                       std::vector<Hotkey> *hotkeys) {
    this->windowManager = windowManager;
    this->page = 0;
    this->selectedShape = nullptr;
    this->hotkeys = hotkeys;

    shapeDrawer = ShapeDrawerFactory::getShapeDrawer(shapeType, windowManager);
    shapeProperties = shapeDrawer->calcShapeProps(windowManager->getWindow());
}

// TODO: move this somewhere else?


void HotkeyPickerDrawer::drawFrame(Hotkey *selectedHotkey) {
    auto start = getPageHotkeyStart();

    shapes.clear();
    shapeDrawer->lastShapePosition = nullptr;

    for (auto it = start; it != hotkeys->end(); ++it) {
        bool selected = &*it == selectedHotkey;

        Shape shape{
                .selected = selected,
                .index = std::distance(hotkeys->begin(), it),
                .hotkey = &*it
        };

        shape = shapeDrawer->drawNextShape(shapeProperties, shape);

        shapes.push_back(shape);

        if (selected) {
            this->selectedShape = &*(this->shapes.end() - 1);
        }
    }
}

std::vector<Hotkey>::iterator HotkeyPickerDrawer::getPageHotkeyStart() {
    int hotkeysPerPage = shapeProperties.itemCounts.y * shapeProperties.itemCounts.x;

    if (page > 0 && hotkeys->size() < hotkeysPerPage) {
        throw OutOfBounds();
    }

    return hotkeys->begin() + hotkeysPerPage * page;
}

int HotkeyPickerDrawer::getHotkeyPage(long index) {
    return (int) (index / (this->shapeProperties.itemCounts.x * this->shapeProperties.itemCounts.y));
}

void HotkeyPickerDrawer::goToHotkey(long hotkeyIdx) {
    Hotkey *hotkey = &*(hotkeys->begin() + hotkeyIdx);

    page = getHotkeyPage(hotkeyIdx);
    drawFrame(hotkey);
}

bool HotkeyPickerDrawer::move(HotkeyPickerMove move) {
    bool canMove = false;
    long newSelectedShapeIdx = 0;

    char* debug;

    switch (move) {
        case LEFT:
            canMove = selectedShape->index >= 1;
            newSelectedShapeIdx = selectedShape->index - 1;
            debug = "LEFT";
            break;
        case RIGHT:
            canMove = selectedShape->index + 1 < hotkeys->size();
            newSelectedShapeIdx = selectedShape->index + 1;
            debug = "RIGHT";
            break;
        case UP:
            canMove = selectedShape->index - 1 - shapeProperties.itemCounts.x >= 0;
            newSelectedShapeIdx = selectedShape->index - shapeProperties.itemCounts.x - 1;
            debug = "UP";
            break;
        case DOWN:
            canMove = selectedShape->index + shapeProperties.itemCounts.x + 1 < hotkeys->size();
            newSelectedShapeIdx = selectedShape->index + shapeProperties.itemCounts.x + 1;
            debug = "DOWN";
            break;
    }

    printf("type: %s, canmove: %d oldIdx: %d newIdx: %d \n", debug, canMove, selectedShape->index, (int)newSelectedShapeIdx);

    if (canMove) {
        goToHotkey(newSelectedShapeIdx);
    }

    return canMove;
}

Hotkey *HotkeyPickerDrawer::getSelectedHotkey() {
    return selectedShape->hotkey;
}


