cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

add_library(pacman SHARED
        src/Pacman.cpp)

set_target_properties(pacman PROPERTIES PREFIX "arcade_")

target_include_directories(pacman PRIVATE
        include
        ../include
        ../../../include)
