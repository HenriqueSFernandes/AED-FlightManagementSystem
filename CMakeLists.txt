cmake_minimum_required(VERSION 3.26)
project(aed-flights)

set(CMAKE_CXX_STANDARD 17)

add_executable(aed-flights main.cpp
        Airport.cpp
        Airport.h)
