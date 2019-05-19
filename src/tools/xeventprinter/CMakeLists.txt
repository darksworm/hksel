cmake_minimum_required(VERSION 2.6)

project(xeventprinter)

add_executable(xeventprinter main.cpp)

FIND_PACKAGE(X11)

target_link_libraries(xeventprinter ${X11_LIBRARIES})
