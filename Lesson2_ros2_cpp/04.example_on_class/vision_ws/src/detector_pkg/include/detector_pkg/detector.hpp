#ifndef DETECTOR_HPP
#define DETECTOR_HPP


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>
using namespace std;

namespace detector
{
class DetectorNode  : public rclcpp::Node
{
public:
    DetectorNode(const rclcpp::NodeOptions &options);
    ~DetectorNode();

    void pubDetector();
private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr detector_publisher_;

    rclcpp::TimerBase::SharedPtr timer_;//定时器

};
}


#endif  //DETECTOR_HPP