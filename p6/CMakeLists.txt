cmake_minimum_required(VERSION 3.6)
project(p6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp solution.hpp reinas.hpp main.hpp)
add_executable(p6 ${SOURCE_FILES})