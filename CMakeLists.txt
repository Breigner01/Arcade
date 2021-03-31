cmake_minimum_required(VERSION 3.17)
project(arcade)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VERBOSE_MAKEFILE on)

add_compile_options(-Wall -Wextra -Weffc++)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        ../arcade
        ../lib/arcade_ncurses.so
        ../lib/arcade_sdl2.so
        ../lib/arcade_sfml.so
        ../lib/arcade_nibbler.so
        ../lib/arcade_pacman.so)

add_executable(arcade
        src/main.cpp
        src/Core.cpp
        src/Parsing.cpp)

target_link_libraries(arcade PUBLIC dl)

target_include_directories(arcade PUBLIC
        include
        lib/Display/include
        lib/Game/include)

add_subdirectory(lib/Display/Ncurses)
add_subdirectory(lib/Display/SDL)
add_subdirectory(lib/Display/SFML)

add_subdirectory(lib/Game/Pacman)
add_subdirectory(lib/Game/Snake)

add_dependencies(arcade ncurses sdl2 sfml pacman nibbler)

add_custom_command(TARGET arcade POST_BUILD
        COMMAND cp arcade ..)