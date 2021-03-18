cmake_minimum_required(VERSION 3.17)
project(B_OOP_400_PAR_4_1_arcade_coline_seguret)

set(CMAKE_CXX_STANDARD 17)

add_executable(arcade
        src/main.cpp)

target_include_directories(arcade PRIVATE
        include)

add_subdirectory(lib/TotoLib)

add_dependencies(arcade toto)

install(TARGETS arcade
        CONFIGURATIONS Release
        RUNTIME DESTINATION .)