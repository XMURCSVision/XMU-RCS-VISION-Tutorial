#ifndef DETECTOR_NODE_HPP
#define DETECTOR_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <string>
using namespace std;

namespace detector
{
    class DetectorNode : public rclcpp::Node
    {
    public:
        explicit DetectorNode(const rclcpp::NodeOptions &options); // 因为注册成了components，所以搭配使用NodeOptions // explicit防止隐式调用
        ~DetectorNode();

        void pubDetector();

    private:
        rclcpp::Publisher<auto_aim_interfaces::msg::armor>::SharedPtr detector_publisher_;
        rclcpp::TimerBase::SharedPtr timer_; // 一个定时器，让消息按计时持续发送
        // detector_pub_;
    };

} // detector

#endif // DETECTOR_NODE_HPP