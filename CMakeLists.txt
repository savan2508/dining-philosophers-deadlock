cmake_minimum_required(VERSION 3.29)
project(dining-philosophers-deadlock)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(dining-philosophers-deadlock
        main.cpp)