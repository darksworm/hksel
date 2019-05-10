cmake_minimum_required(VERSION 2.6)

project(HKSEL)

add_executable(HKSEL main.cpp windowmanager.cpp keyboardmanager.cpp keyboardmanager.h lib/keycode/keycode.h)
add_subdirectory(lib/keycode)

FIND_PACKAGE(X11)
FIND_LIBRARY(YAML_LIB yaml-cpp)

target_link_libraries(HKSEL ${X11_LIBRARIES})
target_link_libraries(HKSEL ${YAML_LIB})
