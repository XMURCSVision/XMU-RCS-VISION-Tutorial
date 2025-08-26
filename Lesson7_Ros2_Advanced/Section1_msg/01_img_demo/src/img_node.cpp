#include "img_demo/img_node.hpp"

ImgNode::ImgNode(const std::string img_path, int binary_thres) : rclcpp::Node("image_node")
{
    this->img_bgr = cv::imread(img_path);
    this->binary_thres = binary_thres;

    img_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
        "/image/show", rclcpp::QoS(10));
    img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image/show",           // 订阅话题名
        rclcpp::SensorDataQoS(), // QoS 设置（也可以用 rclcpp::QoS(10)）
        std::bind(&ImgNode::ImgCallback, this, std::placeholders::_1));

    timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&ImgNode::ImgPublish, this));
}

ImgNode::~ImgNode() {}

void ImgNode::ImgPublish()
{

    if (!this->img_bgr.empty())
    {
        // 转换为 ROS2 消息并发布
        auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", img_bgr).toImageMsg();
        // cv_bridge::CvImage返回的是sensor_msgs::msg::Image::SharedPtr
        img_pub_->publish(*msg); // 取内容
        RCLCPP_INFO(rclcpp::get_logger("img pub"), "Image published");
    }
    else
    {
        RCLCPP_WARN(rclcpp::get_logger("img pub"), "Image is empty");
    }
}

void ImgNode::ImgCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    RCLCPP_INFO(rclcpp::get_logger("img sub"), "Received image !");

    cv::Mat latest_img = cv_bridge::toCvCopy(msg, "bgr8")->image;

    cv::imshow("Image from Ros2", latest_img);
    cv::waitKey(4000);
}