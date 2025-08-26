#include "thres_pkg/thres.hpp"

namespace armor
{
    DetectNode::DetectNode(const rclcpp::NodeOptions &options) : Node("detect_node", options)
    {

        // 声明参数并设置范围描述符
        rcl_interfaces::msg::ParameterDescriptor thresh_desc;
        thresh_desc.description = "binary thres(0-255)";
        thresh_desc.integer_range.resize(1);
        thresh_desc.integer_range[0].from_value = 0;
        thresh_desc.integer_range[0].to_value = 255;
        thresh_desc.integer_range[0].step = 1;

        // 声明参数
        this->binary_thres = declare_parameter("thresh", 60, thresh_desc);

        // 添加参数回调
        param_callback_handle_ = this->add_on_set_parameters_callback(
            std::bind(&ImgNode::parametersCallback, this, std::placeholders::_1));

        binary_img_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
            "/image/binary", rclcpp::SensorDataQoS());
        img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/image/show",
            rclcpp::SensorDataQoS(),
            std::bind(&ImgNode::ImgCallback, this, std::placeholders::_1));
    }

    DetectNode::~DetectNode() {}

    void DetectNode::ImgCallback(const sensor_msgs::msg::Image::SharedPtr msg)
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
        const std::vector<rclcpp::Parameter> &parameters)
    {
        auto result = rcl_interfaces::msg::SetParametersResult();
        result.successful = true;

        for (const auto &param : parameters) // 遍历vector容器中的每一个元素
        {
            if (param.get_name() == "thresh")
            {
                // 更新阈值
                this->binary_thres = param.as_int();
                RCLCPP_INFO(this->get_logger(), "阈值已更新为: %d", this->binary_thres);
            }
        }
        return result;
    }
} // thres
#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(armor::DetectNode)