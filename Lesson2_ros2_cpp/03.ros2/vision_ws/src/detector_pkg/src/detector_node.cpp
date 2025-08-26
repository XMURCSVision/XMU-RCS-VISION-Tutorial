#include "detector_pkg/detector_node.hpp"

namespace detector
{
    DetectorNode::DetectorNode(const rclcpp::NodeOptions &options) : rclcpp::Node("detector_node", options)
    {
        detector_publisher_ = this->create_publisher<std_msgs::msg::String>("/armor_detector/img_raw", 10);

        timer_ = this->create_wall_timer(                 // 使用定时器，每1秒发布一次
            std::chrono::seconds(1),                      // C++标准库里用于时间处理的工具
            std::bind(&DetectorNode::pubDetector, this)); // bind绑定
    }

    DetectorNode::~DetectorNode()
    {
    }

    void DetectorNode::pubDetector()
    {
        auto msg = std_msgs::msg::String(); // 自动类型推导，以及消息的构造函数
        msg.data = "armors of Hero";        // 设置std_msgs::msg::String的data字段

        detector_publisher_->publish(msg); // 调用publish函数，把msg发布出去

        RCLCPP_INFO(this->get_logger(), "Publishing : %s", msg.data.c_str());
    }

} // namespace detector
#include "rclcpp_components/register_node_macro.hpp"    // 这一行宏定义没有要求位置，但是习惯上也是放结尾
RCLCPP_COMPONENTS_REGISTER_NODE(detector::DetectorNode) // 这行宏必须放在.cpp文件的最后一行