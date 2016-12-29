cmake_minimum_required(VERSION 3.6)
project(p6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp reinas.hpp main.hpp extra_functions.hpp)
add_executable(p6 ${SOURCE_FILES})