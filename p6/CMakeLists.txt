cmake_minimum_required(VERSION 3.6)
project(p6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp solution.hpp reinas.hpp main.hpp cmake-build-debug/reinas_bonito.hpp.hpp stats.hpp)
add_executable(p6 ${SOURCE_FILES})