#include "thres_pkg/thres.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<ImgNode>("threshold_node");

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}