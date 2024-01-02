cmake_minimum_required(VERSION 3.27)
project(AED2324_PRJ2_G04)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED2324_PRJ2_G04 main.cpp
        Application.cpp
        Application.h
        Airport.cpp
        Airport.h
        Airline.cpp
        Airline.h
        Graph.cpp
        Graph.h
        Flight.cpp
        Flight.h)

