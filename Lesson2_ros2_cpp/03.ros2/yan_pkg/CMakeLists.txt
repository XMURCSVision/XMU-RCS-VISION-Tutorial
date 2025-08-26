cmake_minimum_required(VERSION 3.8)
project(yan_pkg) # 这是ros2 create时自动生成的

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED) #这是必要的，也是create时自动生成的



# 以下3段是我们要加的

# 我们的node1
find_package(rclcpp REQUIRED)

# 添加可执行程序
add_executable(cpp_node1 src/cpp_node1.cpp)

# hpp搜索路径，一定要放在add_executable后面
target_include_directories(cpp_node1
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接依赖项，即绑定executable和rclcpp
ament_target_dependencies(cpp_node1 rclcpp) 

# 安装可执行文件
install(TARGETS
  cpp_node1
  DESTINATION lib/${PROJECT_NAME}
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
