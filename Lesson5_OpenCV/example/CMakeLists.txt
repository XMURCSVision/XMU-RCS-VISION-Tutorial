cmake_minimum_required(VERSION 3.8)
project(display_sentry)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(display src/display.cpp)

target_link_libraries(display ${OpenCV_LIBS})