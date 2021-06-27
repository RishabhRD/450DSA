cmake_minimum_required(VERSION 3.5)
file(GLOB_RECURSE SOURCES "./*".cc)

SET(CMAKE_CXX_FLAGS "-std=c++2a")

add_executable(binary ${SOURCES})
