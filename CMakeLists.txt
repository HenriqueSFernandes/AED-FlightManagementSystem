cmake_minimum_required(VERSION 3.26)
project(aed-flights)

set(CMAKE_CXX_STANDARD 17)

add_executable(aed-flights main.cpp
        src/Airport.cpp
        src/Airport.h
        src/Airline.cpp
        src/Airline.h
        src/Flight.cpp
        src/Flight.h
        src/Graph.h
        src/ManagementSystem.cpp
        src/ManagementSystem.h
        src/Menu.cpp
        src/Menu.h
        Image/iterators.cpp
        Image/PNG.hpp
        Image/PNG.cpp
        Image/Script.cpp
        Image/Color.cpp
        Image/Image.cpp
        Image/Image.cpp
)
