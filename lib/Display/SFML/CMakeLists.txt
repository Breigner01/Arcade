cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

add_library(sfml SHARED
        src/SFML.cpp)

set_target_properties(sfml PROPERTIES PREFIX "arcade_")

target_link_libraries(sfml PRIVATE
        sfml-audio
        sfml-graphics
        sfml-network
        sfml-system
        sfml-window)

target_include_directories(sfml PRIVATE
        include
        ../include
        ../../../include)

add_custom_command(TARGET sfml POST_BUILD
        COMMAND cp arcade_sfml.so ../../../../lib)
