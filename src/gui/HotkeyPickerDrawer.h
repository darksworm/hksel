#pragma once

#include <X11/Xutil.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>

#include "../hotkey/hotkey.h"
#include "Shape.h"
#include "drawer/ShapeDrawer.h"
#include "WindowManager.h"
#include "drawer/ShapeDrawerFactory.h"

enum class HotkeyPickerMove {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class HotkeyPickerDrawer {
private:
    WindowManager *windowManager;

    ShapeProperties shapeProperties;
    ShapeDrawer* shapeDrawer;

    Shape *selectedShape;
    int page = 0;

    std::vector<Hotkey> *hotkeys;
    std::vector<Shape> shapes;

    std::vector<Hotkey>::iterator getPageHotkeyStart();

    int getHotkeyPage(long index);

    void goToHotkey(long hotkeyIdx);

public:
    HotkeyPickerDrawer(WindowManager* windowManager, ShapeType shapeType, std::vector<Hotkey> *hotkeys);

    void drawFrame(Hotkey* selectedHotkey);

    bool move(HotkeyPickerMove move);

    Hotkey* getSelectedHotkey();
};


