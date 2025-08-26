cmake_minimum_required(VERSION 3.8)
project(sub_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)

# 头文件包含路径
include_directories(
  include
)

# 编译为库
add_library(sub_pkg  # 注册了一个<target_name>，规范上这里放包名
  SHARED                  #生成动态链接库，与之相对的是静态库STATIC
  src/sub_node.cpp
)

# 链接依赖 
ament_target_dependencies(sub_pkg
  rclcpp 
  std_msgs
  rclcpp_components
)

# 注册组件（这会生成插件描述 xml）
rclcpp_components_register_nodes(sub_pkg   # 这里填的是上面add_library所注册的<target_name>
  "sub::SubNode"                      # 格式是 namespace::class
)

# 安装头文件
install(DIRECTORY include/
  DESTINATION include/
)

# 安装库文件
install(TARGETS sub_pkg
  LIBRARY DESTINATION lib
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
