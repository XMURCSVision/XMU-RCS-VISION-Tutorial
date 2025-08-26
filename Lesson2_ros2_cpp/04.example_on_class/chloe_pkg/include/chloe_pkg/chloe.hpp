#include "rclcpp/rclcpp.hpp"
#include <string>

using namespace std;

class MyNode : public rclcpp::Node
{
public:
    MyNode(string nodename) : Node(nodename)
    {
        RCLCPP_INFO(this->get_logger(), "nodename: %s", nodename.c_str());
    }

    ~MyNode() {}
};
