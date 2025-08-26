cmake_minimum_required(VERSION 3.22)
project(display) # project name

find_package( OpenCV REQUIRED ) # 找到OpenCV依赖

include_directories( ${OpenCV_INCLUDE_DIRS} ) # 添加OpenCV include目录

add_executable( display src/imshow.cpp ) # 可执行文件

target_link_libraries( display ${OpenCV_LIBS} ) # 链接