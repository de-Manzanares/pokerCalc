cmake_minimum_required(VERSION 3.26)
project(pokerCalc)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(pokerCalc source/main.cpp
        source/probCalc.cpp
        source/funWithFunctions.cpp)
