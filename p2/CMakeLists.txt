cmake_minimum_required(VERSION 2.8.4)
project(p2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(p2 COMMAND make -C ${p2_SOURCE_DIR}
                         CLION_EXE_DIR=${PROJECT_BINARY_DIR})
