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

    XClearWindow(windowManager->getDisplay(), windowManager->getWindow());
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

        if (selected) {
            this->selectedShape = &shape;
        }

        shapes.push_back(shape);
    }
}

std::vector<Hotkey>::iterator HotkeyPickerDrawer::getPageHotkeyStart() {
    int hotkeysPerPage = shapeProperties.rows * shapeProperties.columns;

    if (page > 0 && hotkeys->size() < hotkeysPerPage) {
        throw OutOfBounds();
    }

    return hotkeys->begin() + hotkeysPerPage * page;
}

int HotkeyPickerDrawer::getHotkeyPage(long index) {
    return (int) (index / (this->shapeProperties.columns * this->shapeProperties.rows));
}

void HotkeyPickerDrawer::goToHotkey(long hotkeyIdx) {
    Hotkey *hotkey = &*(hotkeys->begin() + hotkeyIdx);

    page = getHotkeyPage(hotkeyIdx);
    drawFrame(hotkey);
}

void HotkeyPickerDrawer::move(HotkeyPickerMove move) {
    bool canMove = false;
    long newSelectedShapeIdx = 0;

    switch (move) {
        case HotkeyPickerMove::LEFT:
            canMove = selectedShape->index >= 1;
            newSelectedShapeIdx = selectedShape->index - 1;
            break;
        case HotkeyPickerMove::RIGHT:
            canMove = selectedShape->index + 1 < hotkeys->size();
            newSelectedShapeIdx = selectedShape->index + 1;
            break;
        case HotkeyPickerMove::TOP:
            canMove = selectedShape->index - shapeProperties.columns >= 0;
            newSelectedShapeIdx = selectedShape->index - shapeProperties.columns;
            break;
        case HotkeyPickerMove::DOWN:
            canMove = selectedShape->index + shapeProperties.columns < hotkeys->size();
            newSelectedShapeIdx = selectedShape->index + shapeProperties.columns;
            break;
    }

    if (canMove) {
        goToHotkey(newSelectedShapeIdx);
    }
}

Hotkey *HotkeyPickerDrawer::getSelectedHotkey() {
    return selectedShape->hotkey;
}


