cmake_minimum_required(VERSION 3.8)
project(detector)

find_package(OpenCV REQUIRED)

# 添加include目录
include_directories(include)

# 添加你的源文件
add_executable(detector
    src/main.cpp
    src/light_detector.cpp
    src/pnp_solver.cpp
)

# 链接 OpenCV 库
target_link_libraries(detector
    ${OpenCV_LIBS}
)
