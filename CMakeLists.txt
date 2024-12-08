cmake_minimum_required(VERSION 3.20)
project(KNearestNeighbors LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Base directories
set(PROJDIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRCDIR ${PROJDIR}/src)
set(BINDIR ${PROJDIR}/bin)

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINDIR})

# Include directories
set(DIRS calculations commands containers io networking threading utils)
foreach(dir IN LISTS DIRS)
    list(APPEND SOURCEDIRS ${SRCDIR}/${dir})
endforeach()
include_directories(${SOURCEDIRS})

# Collect all source files (excluding main programs)
file(GLOB_RECURSE SOURCES ${SRCDIR}/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX ".*(ClientProgram|ServerProgram|Program)\\.cpp$")

# Object library for shared sources
add_library(common_objs OBJECT ${SOURCES})

# Define executables
add_executable(client ${SRCDIR}/ClientProgram.cpp $<TARGET_OBJECTS:common_objs>)
add_executable(server ${SRCDIR}/ServerProgram.cpp $<TARGET_OBJECTS:common_objs>)

# Cross-platform linking for threading
find_package(Threads REQUIRED)
target_link_libraries(client PRIVATE Threads::Threads)
target_link_libraries(server PRIVATE Threads::Threads)

# Custom clean command
add_custom_target(fresh
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BINDIR}
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning done!"
)

# Print status messages
message(STATUS "Project source directory: ${SRCDIR}")
message(STATUS "Binaries will be in: ${BINDIR}")
