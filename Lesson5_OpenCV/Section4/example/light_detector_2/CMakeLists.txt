cmake_minimum_required(VERSION 3.8)
project(light_detector_2)

find_package(OpenCV REQUIRED)

# 添加include目录
include_directories(include)

# 添加你的源文件
add_executable(light_detector_2
    src/main.cpp
    src/light_detector.cpp
)

# 链接 OpenCV 库
target_link_libraries(light_detector_2
    ${OpenCV_LIBS}
)
