cmake_minimum_required(VERSION 3.8)
project(task)

# find package
find_package(OpenCV REQUIRED)

# add_executable
add_executable(pixel src/01_pixel.cpp)
add_executable(channel src/02_channel.cpp)
add_executable(roi src/03_roi_1.cpp)
add_executable(roi src/03_roi_2.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries( ${project}
    ${OpenCV_LIBS})