cmake_minimum_required(VERSION 3.15)
project(KNearestNeighbors CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Base directories
set(PROJDIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRCDIR ${PROJDIR}/src)
set(BINDIR ${PROJDIR}/bin)

# Include directories
set(DIRS calculations commands containers io networking threading utils)
foreach(dir IN LISTS DIRS)
    list(APPEND SOURCEDIRS ${SRCDIR}/${dir})
endforeach()

include_directories(${SOURCEDIRS})

# Collect all source files
file(GLOB_RECURSE SOURCES ${SRCDIR}/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX ".*(ClientProgram|ServerProgram|Program)\\.cpp$")

# Define output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINDIR})

# Create object library for shared sources
add_library(common_objs OBJECT ${SOURCES})

# Main programs
add_executable(client $<TARGET_OBJECTS:common_objs> ${SRCDIR}/ClientProgram.cpp)
add_executable(server $<TARGET_OBJECTS:common_objs> ${SRCDIR}/ServerProgram.cpp)

# Link pthread
target_link_libraries(client pthread)
target_link_libraries(server pthread)

# Custom clean command
add_custom_target(fresh
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BINDIR}
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning done!"
)
