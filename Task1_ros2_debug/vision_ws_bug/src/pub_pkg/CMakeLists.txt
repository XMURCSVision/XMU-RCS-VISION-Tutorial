cmake_minimum_required(VERSION 3.8)
project(pub_pkg)

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
add_library(pub_pkg  
  SHARED                  
  pub_node.cpp
)

# 链接依赖 
ament_target_dependencies(pub_pkg 
  rclcpp
  std_msgs
  rclcpp_components
)

# 注册组件（这会生成插件描述 xml）
rclcpp_components_register_nodes(pub_pkg   
  "pub::PubNode"                      
)

# 安装头文件
install(DIRECTORY include/
  DESTINATION include/
)

# 安装库文件
install(TARGETS pub_pkg
  LIBRARY DESTINATION lib
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


ament_package()
