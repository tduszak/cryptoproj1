cmake_minimum_required(VERSION 3.10)

project(cryptoproj1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cryptoproj1 algo.h algo.cpp main.cpp)
add_executable(project1_submission division_algorithm.cpp)
add_executable(project2_vigenere project2/src/main.cpp)
