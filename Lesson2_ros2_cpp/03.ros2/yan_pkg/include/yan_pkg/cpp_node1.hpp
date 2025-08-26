#include <iostream>
#include <string>
#include "rclcpp/rclcpp.hpp"
using namespace std;
class MyNode : public rclcpp::Node
{
public:
    MyNode(string node_name) : Node(node_name) // 设置节点名字
    {
        RCLCPP_INFO(this->get_logger(), "Node:rm_vision");
    }
};
