cmake_minimum_required(VERSION 2.6)

project(HKSEL)

add_executable(HKSEL main.cpp)

FIND_PACKAGE(X11)
target_link_libraries(HKSEL ${X11_LIBRARIES})
