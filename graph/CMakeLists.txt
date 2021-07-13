cmake_minimum_required(VERSION 3.5)
project(graph)
SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET (CMAKE_C_COMPILER "/usr/bin/clang")
SET (CMAKE_CXX_FLAGS "-std=c++20 -Wall \
-Wextra \
-Wshadow \
-Wnon-virtual-dtor \
-Wold-style-cast \
-Wcast-align \
-Wunused \
-Woverloaded-virtual \
-Wconversion \
-Wsign-conversion \
-Wformat=2 \
-Wdouble-promotion \
")
file(GLOB SOURCES "*.cc")


add_executable(binary ${SOURCES})
