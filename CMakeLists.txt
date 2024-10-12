cmake_minimum_required(VERSION 3.22)
project(Tetris VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CXX_FLAGS "${CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

add_subdirectory(raylib)
add_compile_definitions(RAYGUI_IMPLEMENTATION)
add_subdirectory(raygui/projects/CMake)
add_subdirectory(googletest)

enable_testing()

add_library(core
    src/autorepeat.cpp
    src/input.cpp
    src/piece.cpp
    src/pieces.cpp
    src/piece_generator.cpp
    src/playfield.cpp
    src/renderer.cpp
    src/tetris.cpp
    src/tetris_internal.cpp
)

target_include_directories(core
    PUBLIC include
    PUBLIC raylib/src
    PUBLIC raygui/src
)

target_link_libraries(core
    PRIVATE raygui
    PRIVATE raylib
)

add_executable(main
    src/main.cpp
)

target_link_libraries(main
    PRIVATE core
)

add_executable(unittest
    unittest/main.cpp
    unittest/playfield_test.cpp
)

add_test(NAME unittest COMMAND unittest)

target_include_directories(unittest
    PRIVATE include
    PRIVATE googletest/googletest/include
    PRIVATE googletest/googlemock/include
)

target_link_libraries(unittest
    PRIVATE core
    PRIVATE gtest
    PRIVATE gmock
)

add_custom_command(
    TARGET unittest
    POST_BUILD
    COMMAND ctest ARGS --verbose
)
