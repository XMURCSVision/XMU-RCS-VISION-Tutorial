#include "img_demo/img_node.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold>" << std::endl;
        return 1;
    }

    auto node = std::make_shared<ImgNode>(argv[1], std::stoi(argv[2]));

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}