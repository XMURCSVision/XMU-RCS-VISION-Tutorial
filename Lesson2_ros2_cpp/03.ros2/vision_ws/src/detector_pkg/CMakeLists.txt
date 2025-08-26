cmake_minimum_required(VERSION 3.8)
project(detector_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)

# 头文件包含路径
include_directories(
  include
)

# 编译为库
add_library(detector_pkg  # 注册了一个<target_name>，规范上这里放包名
  SHARED                  #生成动态链接库，与之相对的是静态库STATIC
  src/detector_node.cpp
)

# 链接依赖 
ament_target_dependencies(detector_pkg
  rclcpp 
  std_msgs
  rclcpp_components
)

# 注册组件（这会生成插件描述 xml）
rclcpp_components_register_nodes(detector_pkg   # 这里填的是上面add_library所注册的<target_name>
  "detector::DetectorNode"                      # 格式是 namespace::ClassName
)

# 安装头文件
install(DIRECTORY include/
  DESTINATION include/
)

# 安装库文件
install(TARGETS detector_pkg
  LIBRARY DESTINATION lib
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


ament_package()
