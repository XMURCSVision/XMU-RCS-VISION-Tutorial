#include "detector/detector.hpp"

int main(int argc, char *argv[])
{
    //====== 1.处理命令行所传入的参数 ======
    // 检查参数数量(防爆)
    if (argc < 4)
    {
        std::cerr << "用法: " << argv[0] << " <图像路径> <阈值>" << std::endl;
        return -1;
    }

    // 读取图像路径和阈值参数
    std::string image_path = argv[1];
    int binary_thres = std::stoi(argv[2]); // 转换为 int
    int detect_color = std::stoi(argv[3]);

    // 读取图像
    cv::Mat bgr_img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (bgr_img.empty())
    {
        std::cerr << "无法读取图像: " << image_path << std::endl;
        return -1;
    }
    std::cout << "1" << std::endl;

    // ====== 2.初始化一个Detector对象 ======
    Detector *detector_;
    std::cout << "2" << std::endl;

    // ====== 3.preprocess RGB->GRAY->binary ======
    auto binary_img = detector_->preprocessImage(bgr_img, binary_thres);
    std::cout << "3" << std::endl;

    // ====== 4.死在这里了
    auto lights_ = detector_->findLights(bgr_img, binary_img);
    std::cout << "4" << std::endl;

    // ====== 5.
    auto armors_ = detector_->matchLights(lights_, detect_color);
    std::cout << "5" << std::endl;

    detector_->drawResults(bgr_img, lights_, armors_);
    std::cout << "detect" << std::endl;

    return 0;
}