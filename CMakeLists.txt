cmake_minimum_required (VERSION 3.4)
project (spline)

# Mitigation
file(GLOB_RECURSE SPLINE_SOURCES LIST_DIRECTORIES true src/*.h src/*.cpp)
add_executable(spline ${SPLINE_SOURCES})