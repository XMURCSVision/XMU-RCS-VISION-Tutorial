cmake_minimum_required(VERSION 3.8)
project(light_detector_1)

find_package(OpenCV REQUIRED)

# 添加include目录
include_directories(include)

# 添加你的源文件
add_executable(detector_1
    src/main.cpp
    src/light_detector.cpp
)

# 链接 OpenCV 库
target_link_libraries(detector_1
    ${OpenCV_LIBS}
)
