cmake_minimum_required(VERSION 3.1)

project(lambda)

set(CMAKE_CXX_STANDARD 11)
set(FLAGS "-g -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -Wall -Wpedantic -Wextra -Wfatal-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories(
    include
)

add_library(lambda
    src/axis_angle.cpp
    src/complex.cpp
    src/dynamic_matrix.cpp
    src/echelon.cpp
    src/levenshtein.cpp
    src/matrix.cpp
    src/quaternion.cpp
    src/solve.cpp
    src/elementary_automata.cpp
)

add_executable(main src/main.cpp)
target_link_libraries(main lambda)
add_executable(tests
    test/catch_main.cpp
    test/complex_tests.cpp
    test/dynamic_matrix_tests.cpp
    test/kalman_tests.cpp
    test/levenshtein_tests.cpp
    test/matrix_tests.cpp
    test/solve_tests.cpp
    test/automata_tests.cpp
    test/decomposition_tests.cpp
)

target_link_libraries(tests lambda)
