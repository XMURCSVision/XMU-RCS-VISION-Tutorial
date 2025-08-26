#include "img_demo/img_node.hpp"

int main(int argc, char *argv[])
{

    rclcpp::init(argc, argv);

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold>" << std::endl;
        return 1;
    }

    cv::Mat img_bgr = cv::imread(argv[1]);
    int binary_thres = std::stoi(argv[2]); // 转成 int

    auto node = std::make_shared<ImgNode>(img_bgr, binary_thres);

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}