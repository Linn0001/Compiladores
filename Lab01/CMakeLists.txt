cmake_minimum_required(VERSION 4.0)
project(Lab01)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab01 main.cpp
        scanner.cpp
        token.cpp)
