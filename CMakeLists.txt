cmake_minimum_required(VERSION 3.22)
project(Tetris VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CXX_FLAGS "${CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

add_subdirectory(raylib)

add_executable(main
    src/autorepeat.cpp
    src/input.cpp
    src/main.cpp
    src/piece.cpp
    src/piece_generator.cpp
    src/playfield.cpp
    src/renderer.cpp
    src/tetris.cpp
    src/tetris_internal.cpp
)

target_include_directories(main
    PRIVATE include
    PRIVATE raylib/src
)

target_link_libraries(main
    PRIVATE raylib
)
