cmake_minimum_required(VERSION 3.8)
project(bringup_pkg)

find_package(ament_cmake_auto REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package( # 这是一个高级宏封装，在find的时候必须是ament_cmake_auto，而非之前的普通ament_cmake。而且只适合简单的py包，对于cpp不适合
  INSTALL_TO_SHARE
  launch
)
