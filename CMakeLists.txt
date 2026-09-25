cmake_minimum_required(VERSION 3.10)

# use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# project name
project(cryptoproj1)

# location for header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# files used to build the program
add_executable(cryptoproj1 algo.h algo.cpp main.cpp)
