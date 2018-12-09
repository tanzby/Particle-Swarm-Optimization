cmake_minimum_required(VERSION 3.12)
project(PSO)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})


add_subdirectory(test)