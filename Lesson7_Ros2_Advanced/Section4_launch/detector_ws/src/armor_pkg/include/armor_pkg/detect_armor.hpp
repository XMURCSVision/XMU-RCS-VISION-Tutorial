#ifndef THRES_HPP
#define THRES_HPP

#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "auto_aim_interfaces/msg/armor.hpp"
#include <string>
#include <chrono>

namespace armor
{
    class DetectNode : public rclcpp::Node
    {
    public:
        DetectNode(const rclcpp::NodeOptions &options);
        ~DetectNode();
        rcl_interfaces::msg::SetParametersResult parametersCallback(
            const std::vector<rclcpp::Parameter> &parameters);

        void ImgCallback(const sensor_msgs::msg::Image::SharedPtr msg);

    private:
        rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr armor_pub_;

        int binary_thres;

        OnSetParametersCallbackHandle::SharedPtr param_callback_handle_;
    };
}
#endif // THRES_HPP