cmake_minimum_required(VERSION 3.10)
project(solvepnp_demo)

# 寻找 OpenCV
find_package(OpenCV REQUIRED)

# # 设置 C++ 标准
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(pnp_demo pnp_demo.cpp)

# 链接 OpenCV 库
target_link_libraries(pnp_demo ${OpenCV_LIBS})
