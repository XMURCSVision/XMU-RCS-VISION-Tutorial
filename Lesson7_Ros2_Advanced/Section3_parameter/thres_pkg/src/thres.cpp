#include "thres_pkg/thres.hpp"

ImgNode::ImgNode(std::string node_name) : rclcpp::Node(node_name)
{
    // 声明参数并设置范围描述符
    rcl_interfaces::msg::ParameterDescriptor thresh_desc; // descriptor
    thresh_desc.description = "binary_thres(0-255)";
    thresh_desc.integer_range.resize(1); // 分配一个 IntegerRange 元素
    thresh_desc.integer_range[0].from_value = 0;
    thresh_desc.integer_range[0].to_value = 255;
    thresh_desc.integer_range[0].step = 1;

    // 声明参数
    this->binary_thres = declare_parameter("thresh", 60, thresh_desc);

    // 添加参数回调
    param_callback_handle_ = this->add_on_set_parameters_callback(
        std::bind(&ImgNode::parametersCallback, this, std::placeholders::_1));

    img_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
        "/image/show", rclcpp::SensorDataQoS());
    binary_img_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
        "/image/binary", rclcpp::SensorDataQoS());
    img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image/show",
        rclcpp::SensorDataQoS(),
        std::bind(&ImgNode::ImgCallback, this, std::placeholders::_1));

    timer_ = this->create_wall_timer(std::chrono::milliseconds(100),
                                     std::bind(&ImgNode::ImgPublish, this));
}

ImgNode::~ImgNode() {}

void ImgNode::ImgPublish()
{
    RCLCPP_INFO(this->get_logger(), "img_bgr size: %dx%d type: %d", img_bgr.cols, img_bgr.rows, img_bgr.type());

    if (!this->img_bgr.empty())
    {
        std_msgs::msg::Header header;
        header.stamp = this->now();
        header.frame_id = "camera_frame";

        cv::Mat img_to_publish = img_bgr;
        if (img_bgr.type() != CV_8UC3)
        {
            img_bgr.convertTo(img_to_publish, CV_8UC3, 1.0 / 256);
        }
        auto msg = cv_bridge::CvImage(header, "bgr8", img_to_publish).toImageMsg();
        img_pub_->publish(*msg);
        // cv_bridge::CvImage返回的是sensor_msgs::msg::Image::SharedPtr
        RCLCPP_INFO(this->get_logger(), "Image published");
    }
    else
    {
        RCLCPP_WARN(this->get_logger(), "Image is empty");
    }
}

void ImgNode::ImgCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received image !");
    try
    {
        cv::Mat latest_img = cv_bridge::toCvCopy(msg, "bgr8")->image;
        cv::Mat binary_img;

        // 使用当前binary_thres值进行阈值处理
        cv::threshold(latest_img, binary_img, this->binary_thres, 255, cv::THRESH_BINARY);

        std_msgs::msg::Header header;
        header.stamp = this->now();
        header.frame_id = "camera_frame";
        auto msg_binary = cv_bridge::CvImage(header, "mono8", binary_img).toImageMsg();

        // 3. 发布
        binary_img_pub_->publish(*msg_binary);
    }
    catch (const cv_bridge::Exception &e)
    {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge error: %s", e.what());
    }
}

// 参数回调函数
rcl_interfaces::msg::SetParametersResult ImgNode::parametersCallback(
    const std::vector<rclcpp::Parameter> &parameters) // 动态调参
{
    auto result = rcl_interfaces::msg::SetParametersResult();
    result.successful = true;

    for (const auto &param : parameters) // vector
    {
        if (param.get_name() == "thresh")
        {
            // 更新阈值
            this->binary_thres = param.as_int(); // get_parameter("thresh").as_int()
            RCLCPP_INFO(this->get_logger(), "阈值已更新为: %d", this->binary_thres);
        }
    }
    return result;
}