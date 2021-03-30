cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

add_library(sfml SHARED
        src/SFML.cpp)

set_target_properties(sfml PROPERTIES PREFIX "arcade_")

target_link_libraries(ncurses
        PUBLIC sfml-audio
        PUBLIC sfml-graphics
        PUBLIC sfml-network
        PUBLIC sfml-system
        PUBLIC sfml-window)

target_include_directories(sfml PRIVATE
        include
        ../include
        ../../../include)

add_custom_command(TARGET sfml POST_BUILD
        COMMAND cp arcade_sfml.so ../..)
