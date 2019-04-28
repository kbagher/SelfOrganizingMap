cmake_minimum_required(VERSION 3.13)
project(DistributedSOM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DistributedSOM
        SampleCode.cpp
        SOM.cpp
        SOM.h
        )
