#include "pub_pkg/pub_node.hpp"

namespace pub
{
    PubNode::PubNode(const rclcpp::NodeOptions &options) : rclcpp::Node("pub_node", options)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("/information", 10)

                         timer_ = this->create_wall_timer( // 使用定时器，每1秒发布一次
            std::chrono::seconds(1),                       // C++标准库里用于时间处理的工具
            std::bind(&PubNode::toPublish, this));         // bind绑定
    }

    PubNode::~PubNode()
    {
    }

    void PubNode::toPublish()
    {
        auto msg = std_msgs::msg::String();
        msg.data = "Task1 : ros2 ws debug";

        publisher_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "Publishing : %s", msg.data.c_str());
    }

} // namespace detector
#include "rclcpp_components/register_node_macro.hpp" // 这一行宏定义没有要求位置，但是习惯上也是放结尾
RCLCPP_COMPONENTS_REGISTER_NODE(pub::PubNode)        // 这行宏必须放在.cpp文件的最后一行