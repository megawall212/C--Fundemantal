cmake_minimum_required(VERSION 3.30)
project(Lab_2__classes)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_2__classes vehicle.cpp
        vehicle.h
        Showroom.cpp
        Showroom.h
        Dealership.cpp
        Dealership.h
        main.cpp)
