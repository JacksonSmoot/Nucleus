cmake_minimum_required(VERSION 3.31)
project(Nucleus2 C)

set(CMAKE_C_STANDARD 23)

include_directories(src headers)

find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
find_library(OBJC_LIBRARY objc REQUIRED)

add_executable(Nucleus2 src/main.c
        headers/nucleus_core.h
        src/mac_arm64_core.c
        headers/objective_c_headers.h
        headers/objc_mac_gui.h)

add_custom_command(
        TARGET Nucleus2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/imgs/dev_icon.png
        $<TARGET_FILE_DIR:Nucleus2>/dev_icon.png
        COMMENT "Copying icon.jpg to build output directory"
)

target_link_libraries(Nucleus2
        ${COCOA_FRAMEWORK}
        ${OBJC_LIBRARY}
)