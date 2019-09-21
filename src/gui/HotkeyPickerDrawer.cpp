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

    auto it = start;
    for (; it != hotkeys->end(); ++it) {
        if (filter && !filter(&*it)) {
            continue;
        }

        if (selectedHotkey == nullptr) {
            selectedHotkey = &*it;
        }

        bool selected = &*it == selectedHotkey;

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

    bool hasNextPage = false;

    if(!filter) {
        hasNextPage = it + 1 < hotkeys->end();
    } else {
        if(++it >= hotkeys->end()) {
            hasNextPage = false;
        } else {
            for (; it != hotkeys->end(); ++it) {
                if (filter && !filter(&*it)) {
                    continue;
                } else {
                    hasNextPage = true;
                    break;
                }
            }
        }
    }

    int circleTypes[] = {0, 0, 0};

    if (hasNextPage) {
        circleTypes[page == 0 ? 0 : 1] = 1;
    } else {
        circleTypes[2] = 1;
    }

    GC gc = XCreateGC(windowManager->getDisplay(), windowManager->getWindow(), 0, nullptr);

    XSetForeground(windowManager->getDisplay(), gc, WhitePixel(windowManager->getDisplay(), DefaultScreen(windowManager->getDisplay())));
    XSetBackground(windowManager->getDisplay(), gc, DefaultScreen(windowManager->getDisplay()));
    XSetFillStyle(windowManager->getDisplay(), gc, FillSolid);
    XSetLineAttributes(windowManager->getDisplay(), gc, 2, LineSolid, CapRound, JoinRound);

    int i = 0;
    for (const int &circleType : circleTypes) {
        auto dia = 15;
        auto spacing = 10;
        auto xPos = windowDimensions->x - 35;
        auto baseYPos = windowDimensions->y / 2 - (dia * 1.5) - spacing;
        auto yPos =  baseYPos + (i * (dia + spacing));

        XDrawArc(windowManager->getDisplay(), windowManager->getWindow(), gc, xPos, yPos, dia, dia, 0, 360 * 64);
        if(circleType == 1) {
            XFillArc(windowManager->getDisplay(), windowManager->getWindow(), gc, xPos, yPos, dia, dia, 0, 360 * 64);
        }
        i++;
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

bool HotkeyPickerDrawer::move(HotkeyPickerMove move, unsigned int steps) {
    bool canMove = false;
    long newSelectedShapeIdx = 0;

    char *debug;

    switch (move) {
        case HotkeyPickerMove::LEFT:
            canMove = selectedShape->index >= steps;
            newSelectedShapeIdx = selectedShape->index - steps;
            debug = "LEFT";
            break;
        case HotkeyPickerMove::RIGHT:
            canMove = selectedShape->index + steps < hotkeys->size();
            newSelectedShapeIdx = selectedShape->index + steps;
            debug = "RIGHT";
            break;
        case HotkeyPickerMove::UP:
            canMove = selectedShape->index - (steps * shapeProperties.itemCounts.x) >= 0;
            newSelectedShapeIdx = selectedShape->index - (steps * shapeProperties.itemCounts.x);
            debug = "UP";
            break;
        case HotkeyPickerMove::DOWN:
            canMove = selectedShape->index + (steps * shapeProperties.itemCounts.x) < hotkeys->size();
            newSelectedShapeIdx = selectedShape->index + (steps * shapeProperties.itemCounts.x);
            debug = "DOWN";
            break;
        case HotkeyPickerMove::END:
            canMove = selectedShape->index != hotkeys->size() - 1;
            newSelectedShapeIdx = hotkeys->size() - 1;
            debug = "END";
            break;
        case HotkeyPickerMove::HOME:
            canMove = true;
            newSelectedShapeIdx = 0;
            debug = "HOME";
            break;
        case HotkeyPickerMove::LINE:
            canMove = steps > 0 && shapeProperties.itemCounts.x * steps < hotkeys->size();
            newSelectedShapeIdx = shapeProperties.itemCounts.x * (steps - 1);
            debug = "LINE";
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
