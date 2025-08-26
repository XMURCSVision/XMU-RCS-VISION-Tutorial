cmake_minimum_required(VERSION 3.10)
project(rgb)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(rgb src/trackbar.cpp)
target_link_libraries(rgb ${OpenCV_LIBS})
