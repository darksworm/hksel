#include <utility>

#include "HotkeyPickerDrawer.h"
#include "../exceptions/OutOfBounds.h"
#include "dimensions.h"
#include <memory>

HotkeyPickerDrawer::HotkeyPickerDrawer(WindowManager *windowManager, ShapeType shapeType,
                                       std::vector<Hotkey> *hotkeys) {
    this->windowManager = windowManager;
    this->page = 0;
    this->selectedShape = nullptr;
    this->hotkeys = hotkeys;

    shapeDrawer = ShapeDrawerFactory::getShapeDrawer(shapeType, windowManager);
    shapeProperties = shapeDrawer->calcShapeProps(windowManager->getWindow());
}

void HotkeyPickerDrawer::drawFrame(Hotkey *selectedHotkey) {
    auto start = getPageHotkeyStart();

    shapes.clear();
    shapeDrawer->lastShapePosition = nullptr;

    std::unique_ptr<Dimensions> windowDimensions(new Dimensions);
    windowManager->getWindowDimensions(&windowDimensions->x, &windowDimensions->y);

    int shapeCnt = shapeProperties.itemCounts.x * shapeProperties.itemCounts.y;
    int drawnShapeCnt = 0;

    for (auto it = start; it != hotkeys->end(); ++it) {
        if(filter && !filter(&*it)){
            continue;
        }

        if(selectedHotkey == nullptr){
            selectedHotkey = &*it;
        }

        bool selected =  &*it == selectedHotkey;

        Shape shape{
                .selected = selected,
                .index = std::distance(hotkeys->begin(), it),
                .hotkey = &*it
        };

        shape = shapeDrawer->drawNextShape(shapeProperties, *windowDimensions, shape);

        shapes.push_back(shape);

        if (selected) {
            this->selectedShape = &*(this->shapes.end() - 1);
        }

        if (++drawnShapeCnt >= shapeCnt) {
            break;
        }
    }
}

std::vector<Hotkey>::iterator HotkeyPickerDrawer::getPageHotkeyStart() {
    int hotkeysPerPage = shapeProperties.itemCounts.y * shapeProperties.itemCounts.x;

    if (page > 0 && hotkeys->size() < hotkeysPerPage) {
        throw OutOfBounds();
    }

    int offset = hotkeysPerPage * page;

// TODO: what's the deal with this?
//
//    if(!this->filter) {
        return hotkeys->begin() + offset;
//    } else {
//        int hotkeysFound = 0;
//
//        for (auto it = hotkeys->begin(); it != hotkeys->end(); ++it) {
//            if(filter(&*it)) {
//                if(++hotkeysFound > offset) {
//                    return it;
//                }
//            }
//        }
//
//        throw OutOfBounds();
//    }
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

    char *debug;

    switch (move) {
        case HotkeyPickerMove::LEFT:
            canMove = selectedShape->index >= 1;
            newSelectedShapeIdx = selectedShape->index - 1;
            debug = "LEFT";
            break;
        case HotkeyPickerMove::RIGHT:
            canMove = selectedShape->index + 1 < hotkeys->size();
            newSelectedShapeIdx = selectedShape->index + 1;
            debug = "RIGHT";
            break;
        case HotkeyPickerMove::UP:
            canMove = selectedShape->index - shapeProperties.itemCounts.x >= 0;
            newSelectedShapeIdx = selectedShape->index - shapeProperties.itemCounts.x;
            debug = "UP";
            break;
        case HotkeyPickerMove::DOWN:
            canMove = selectedShape->index + shapeProperties.itemCounts.x < hotkeys->size();
            newSelectedShapeIdx = selectedShape->index + shapeProperties.itemCounts.x;
            debug = "DOWN";
            break;
    }

    printf("type: %s, canmove: %d oldIdx: %d newIdx: %d \n", debug, canMove, selectedShape->index,
           (int) newSelectedShapeIdx);

    if (canMove) {
        goToHotkey(newSelectedShapeIdx);
    }

    return canMove;
}

Hotkey *HotkeyPickerDrawer::getSelectedHotkey() {
    return selectedShape->hotkey;
}

void HotkeyPickerDrawer::setFilter(std::function<bool(Hotkey *)> filter) {
    this->filter = std::move(filter);
}
