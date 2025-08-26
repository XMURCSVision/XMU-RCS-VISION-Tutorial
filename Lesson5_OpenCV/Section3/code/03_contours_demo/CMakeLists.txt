cmake_minimum_required(VERSION 3.8)
project(contours_demo)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# 添加你的源文件
add_executable(contours src/contours.cpp)

# 链接 OpenCV 库
target_link_libraries(contours ${OpenCV_LIBS})
