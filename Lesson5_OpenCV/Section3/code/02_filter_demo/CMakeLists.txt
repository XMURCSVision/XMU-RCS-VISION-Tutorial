cmake_minimum_required(VERSION 3.8)
project(filter_demo)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(blur src/01_blur.cpp)
add_executable(GaussianBlur src/02_GaussianBlur.cpp)
add_executable(medianBlur src/03_medianBlur.cpp)

target_link_libraries(blur ${OpenCV_LIBS} )
target_link_libraries(GaussianBlur ${OpenCV_LIBS} )
target_link_libraries(medianBlur ${OpenCV_LIBS} )