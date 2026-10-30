cmake_minimum_required(VERSION 3.10)

project(cryptoproj1 LANGUAGES CXX)

# Use the same portable language standard for both projects.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Keep the original implementation available without mixing it with current work.
add_executable(cryptoproj1
    project1/legacy/algo.h
    project1/legacy/algo.cpp
    project1/legacy/main.cpp
)

# The standalone Project 1 source still reproduces the archived submission output.
add_executable(project1_submission project1/src/division_algorithm.cpp)

# Keep command-line presentation separate from reusable input and IC calculations.
add_executable(project2_vigenere
    project2/src/main.cpp
    project2/src/ciphertext.h
    project2/src/ciphertext.cpp
    project2/src/coincidence.h
    project2/src/coincidence.cpp
)
