cmake_minimum_required(VERSION 3.1)

project(lambda)

set(FLAGS "-g -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -Wall -Wpedantic -Wextra")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAS "${CMAKE_CXX_FLAGS} ${FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories(include/)

add_library(lambda
    src/matrix.cpp
    src/axis_angle.cpp
    src/quaternion.cpp
    src/complex.cpp
    src/levenshtein.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main lambda)
add_executable(tests
    test/catch_main.cpp
    test/matrix_tests.cpp
    test/complex_tests.cpp
    test/levenshtein_tests.cpp)

target_link_libraries(tests lambda)
