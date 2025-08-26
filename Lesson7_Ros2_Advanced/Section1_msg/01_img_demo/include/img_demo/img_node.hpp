#ifndef IMG_NODE_HPP
#define IMG_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include <string>
#include <chrono>

class ImgNode : public rclcpp::Node
{
public:
    ImgNode(const std::string img_path, int binary_thres);
    ~ImgNode();

    void ImgPublish();
    void ImgCallback(const sensor_msgs::msg::Image::SharedPtr msg);

private:
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr img_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;

    cv::Mat img_bgr;
    int binary_thres;

    rclcpp::TimerBase::SharedPtr timer_;
};

#endif // IMG_NODE_HPP