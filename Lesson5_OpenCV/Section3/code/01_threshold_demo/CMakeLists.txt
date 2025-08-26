cmake_minimum_required(VERSION 3.8)
project(threshold_demo)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# 添加你的源文件
add_executable(threshold src/01_threshold.cpp)
add_executable(adaptive src/02_adaptiveThreshold.cpp)
add_executable(otsu src/03_otsu.cpp)

# 链接 OpenCV 库
target_link_libraries(threshold ${OpenCV_LIBS})
target_link_libraries(adaptive ${OpenCV_LIBS})
target_link_libraries(otsu ${OpenCV_LIBS})

