cmake_minimum_required(VERSION 2.6)

project(HKSEL)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(${PROJECT_NAME} main.cpp gui/WindowManager.cpp input/KeyboardManager.cpp input/KeyboardManager.h hotkey/hotkey.h hotkey/hotkeyloader_yaml.h gui/HotkeyPickerDrawer.cpp gui/HotkeyPickerDrawer.h exceptions/OutOfBounds.h gui/drawer/ShapeDrawer.h gui/Shape.h gui/drawer/RectangleShapeDrawer.cpp gui/drawer/RectangleShapeDrawer.h gui/drawer/ShapeDrawerFactory.cpp gui/drawer/ShapeDrawerFactory.h input/x11_keycodes.h gui/dimensions.h input/handler/InputHandler.h input/handler/InputMode.h input/handler/instruction/InstructionType.h input/handler/filters/FilteringInputHandler.h input/handler/InputHandler.cpp input/handler/filters/FilteringInputHandler.cpp input/handler/filters/KeyFilteringInputHandler.cpp input/handler/filters/KeyFilteringInputHandler.h input/handler/filters/TextFilteringInputHandler.cpp input/handler/filters/TextFilteringInputHandler.h input/handler/InputHandlerFactory.cpp input/handler/InputHandlerFactory.h input/handler/SelectionInputHandler.cpp input/handler/SelectionInputHandler.h input/handler/instruction/Instruction.h input/handler/instruction/MoveInstruction.h input/handler/instruction/ModeChangeInstruction.h input/handler/instruction/FilterInstruction.h)
add_subdirectory(lib/keycode)

FIND_PACKAGE(X11)
FIND_LIBRARY(YAML_LIB yaml-cpp)

target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
target_link_libraries(${PROJECT_NAME} stdc++fs)
target_link_libraries(${PROJECT_NAME} ${YAML_LIB})
target_link_libraries(${PROJECT_NAME} keycode)
