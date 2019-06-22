cmake_minimum_required(VERSION 2.6)

project(keycode)

execute_process(
        COMMAND git submodule update --init ${CMAKE_CURRENT_SOURCE_DIR}/depp-keycode
)

add_library(keycode SHARED
        depp-keycode/src/keycode_id.c
        depp-keycode/src/linux_fromhid.c
        depp-keycode/src/linux_name.c
        depp-keycode/src/linux_rawname.c
        depp-keycode/src/linux_tohid.c
        )

install(TARGETS keycode
        EXPORT keycode-targets
        DESTINATION lib
        )

install(EXPORT keycode-targets
        DESTINATION lib/keycode)

set_target_properties(keycode PROPERTIES PUBLIC_HEADER depp-keycode/src/keycode.h)
