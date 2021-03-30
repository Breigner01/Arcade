cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

add_library(ncurses SHARED
        src/NCURSES.cpp)

set_target_properties(ncurses PROPERTIES PREFIX "arcade_")

target_link_libraries(ncurses PUBLIC curses)

target_include_directories(ncurses PRIVATE
        include
        ../include
        ../../../include)

add_custom_command(TARGET ncurses POST_BUILD
        COMMAND cp arcade_ncurses.so ../..)
