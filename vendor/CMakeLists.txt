cmake_minimum_required(VERSION 3.18)

add_library (boost INTERFACE)
target_include_directories (boost INTERFACE boost_1_74_0)

add_subdirectory(googletest)
