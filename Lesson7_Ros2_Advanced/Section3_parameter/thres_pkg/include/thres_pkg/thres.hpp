#ifndef THRES_HPP
#define THRES_HPP

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
    ImgNode(std::string node_name);
    ~ImgNode();

    void ImgPublish();
    void ImgCallback(const sensor_msgs::msg::Image::SharedPtr msg);

    rcl_interfaces::msg::SetParametersResult parametersCallback(
        const std::vector<rclcpp::Parameter> &parameters);

private:
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr img_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr binary_img_pub_;

    cv::Mat img_bgr_ori = cv::imread("/mnt/f/RM/00.RCS18_summer_course/Lesson7_Ros2_Advanced/Section3_yaml/thres_pkg/images/blue_1.jpg");
    cv::Mar img_bgr;
    int binary_thres;

    rclcpp::TimerBase::SharedPtr timer_;

    OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;
};

#endif // THRES_HPP