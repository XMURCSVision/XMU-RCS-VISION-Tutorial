#include "sub_node.hpp"

namespace sub
{
    SubNode::SubNode(const rclcpp::NodeOptions &options) : rclcpp::Node("sub_node", options)
    {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "/armor_detector", 10,                                             // 话题名和队列长度
            std::bind(&SubNode::topic_callback, this, std::placeholders::_1)); // 绑定回调函数
    }

    SubNode::~SubNode()
    {
    }

    void SubNode::topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "subscription_ received: %s", msg->data.c_str());
    }

}
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(sub::SubNode) // 这行宏必须放在.cpp文件的最后一行
                                              // namespace::ClassName