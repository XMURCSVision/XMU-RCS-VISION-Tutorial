cmake_minimum_required(VERSION 3.8)
project(img_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(cv_bridge REQUIRED)

include_directories(
  include 
  ${OpenCV_INCLUDE_DIRS}
)

add_executable( img_show_node
  src/img_node.cpp
  src/main.cpp
)

ament_target_dependencies(img_show_node
  rclcpp
  cv_bridge
  sensor_msgs
  OpenCV
)

install(TARGETS
  img_show_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
