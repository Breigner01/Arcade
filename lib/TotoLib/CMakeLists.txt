cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

add_library(toto SHARED
        src/TotoClass.cpp)

target_include_directories(toto PRIVATE
        include)