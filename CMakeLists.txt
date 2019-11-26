cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(MrtDistance VERSION 1.0)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB MrtDistanceSrc
    "*.h"
    "*.cpp"
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(MrtDistance ${MrtDistanceSrc})