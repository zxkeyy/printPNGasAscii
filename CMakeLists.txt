cmake_minimum_required(VERSION 3.10)
project(printAscii C)

# Set C standard and enable required
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Main library and executable
add_subdirectory(src)

# Tests (only build if requested)
option(BUILD_TESTS "Build test suite" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()