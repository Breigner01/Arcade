cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

add_library(sfml SHARED
        src/SFML.cpp)

set_target_properties(sfml PROPERTIES PREFIX "arcade_")

target_include_directories(sfml PRIVATE
        include
        ../include
        ../../../include)
