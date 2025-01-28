# Gather all source files from src directory
file(GLOB_RECURSE SRC_FILES
    "core/*.c"
    "preprocessing/*.c"
    "conversion/*.c"
    "io/*.c"
    "utilities/*.c"
)

# Create main library
add_library(printAsciiLib STATIC ${SRC_FILES})

# Include directories
target_include_directories(printAsciiLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external
)

# Create main executable
add_executable(printAscii main.c)
target_link_libraries(printAscii printAsciiLib m)