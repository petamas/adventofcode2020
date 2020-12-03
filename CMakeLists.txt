cmake_minimum_required(VERSION 3.18)

project(AdventOfCode)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(vendor)