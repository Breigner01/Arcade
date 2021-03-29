cmake_minimum_required(VERSION 3.17)
project(arcade)

set(CMAKE_CXX_STANDARD 17)

add_executable(arcade
        src/main.cpp
        src/Core.cpp
        src/Parsing.cpp)

target_link_libraries(arcade PUBLIC dl)

target_include_directories(arcade PRIVATE
        include
        lib/Display/include
        lib/Game/include)

add_subdirectory(lib/Display/Ncurses)
add_subdirectory(lib/Display/SDL)
add_subdirectory(lib/Display/SFML)

add_subdirectory(lib/Game/Pacman)
add_subdirectory(lib/Game/Snake)

add_dependencies(arcade ncurses)
add_dependencies(arcade sdl2)
add_dependencies(arcade sfml)

add_dependencies(arcade pacman)
add_dependencies(arcade nibbler)

install(TARGETS ncurses sdl2 sfml pacman nibbler
        CONFIGURATIONS Release
        LIBRARY DESTINATION lib)

install(TARGETS arcade
        CONFIGURATIONS Release
        RUNTIME DESTINATION .)