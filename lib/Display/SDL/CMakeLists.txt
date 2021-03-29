cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

add_library(sdl2 SHARED
        src/SDL.cpp)

set_target_properties(sdl2 PROPERTIES PREFIX "arcade_")

target_link_libraries(sdl2 PUBLIC SDL2)

target_include_directories(sdl2 PRIVATE
        include
        ../include
        ../../../include)
