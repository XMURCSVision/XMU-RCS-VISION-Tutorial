#ifndef SUB_NODE_HPP // if not define
#define SUB_NODE_HPP // define

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>

using namespace std;

namespace sub
{
    class SubNode : public rclcpp::Node
    {
    public:
        explicit SubNode(const rclcpp::NodeOptions &options);
        ~SubNode();

        void topic_callback(const std_msgs::msg::String::SharedPtr msg);

    private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    };
}

#endif // SUB_NODE_HPP