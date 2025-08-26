#include "yan_pkg/cpp_node1.hpp"

int main(int argc, char *argv[]) // 这个传参当做默认就行
{
    rclcpp::init(argc, argv); // 初始化ROS 2
    auto node1 = std::make_shared<MyNode>("rm_vision");
    rclcpp::spin(node1); // 启动节点node2
    rclcpp::shutdown();  // 清理
    return 0;
}