#include "detector_pkg/detector.hpp"

namespace detector
{
    DetectorNode::DetectorNode(const rclcpp::NodeOptions &options) : rclcpp::Node("detector_node", options)
    {
        detector_publisher_ = this->create_publisher<std_msgs::msg::String>("/armor_detector", 10);

        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&DetectorNode::pubDetector, this));
    }

    DetectorNode::~DetectorNode()
    {
    }

    void DetectorNode::pubDetector()
    {
        auto msg = std_msgs::msg::String();
        msg.data = "armor of Hero";
        detector_publisher_->publish(msg);

        RCLCPP_WARN(this->get_logger(), "publishing :%s", msg.data.c_str());
    }

}

#include "rclcpp_components/register_node_macro.hpp" //这行宏放在cpp最后
RCLCPP_COMPONENTS_REGISTER_NODE(detector::DetectorNode)
