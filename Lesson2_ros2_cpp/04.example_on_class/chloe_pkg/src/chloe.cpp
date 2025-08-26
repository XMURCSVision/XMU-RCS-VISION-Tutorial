#include "chloe_pkg/chloe.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node1 = std::make_shared<MyNode>("rm_vision");
    rclcpp::spin(node1);
    rclcpp::shutdown();

    return 0;
}