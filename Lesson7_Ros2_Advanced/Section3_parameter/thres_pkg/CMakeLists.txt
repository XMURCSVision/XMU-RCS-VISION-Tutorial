cmake_minimum_required(VERSION 3.8)
project(thres_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(rcl_interfaces REQUIRED)

# 添加头文件目录（一般用于自己写的头文件）
include_directories(include)

add_executable(main
  src/main.cpp
  src/thres.cpp)

# 推荐使用 ament_target_dependencies 来添加依赖
ament_target_dependencies(main
  rclcpp
  sensor_msgs
  cv_bridge
  rcl_interfaces
  OpenCV
)

# 如果还是需要 OpenCV 的 include，可以保留 target_include_directories，但不是必须
target_include_directories(main PRIVATE
  ${OpenCV_INCLUDE_DIRS}
)

install(TARGETS main
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
