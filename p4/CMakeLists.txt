cmake_minimum_required(VERSION 3.6)
project(p4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp algorithms.hpp)
add_executable(p4 ${SOURCE_FILES})