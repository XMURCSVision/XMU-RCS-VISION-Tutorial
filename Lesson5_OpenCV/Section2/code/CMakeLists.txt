cmake_minimum_required(VERSION 2.8)
project(section2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(modify src/01_image_modify.cpp)
add_executable(property src/02_image_property.cpp)
add_executable(roi src/03_image_roi.cpp)
add_executable(bgr_split src/04_image_bgr_split.cpp)
add_executable(padding src/05_image_padding.cpp)
add_executable(arithmetic src/06_image_arithmetic.cpp)

target_link_libraries(modify  ${OpenCV_LIBS} )
target_link_libraries(property  ${OpenCV_LIBS} )
target_link_libraries(roi ${OpenCV_LIBS} )
target_link_libraries(bgr_split ${OpenCV_LIBS} )
target_link_libraries(padding ${OpenCV_LIBS} )
target_link_libraries(arithmetic ${OpenCV_LIBS} )