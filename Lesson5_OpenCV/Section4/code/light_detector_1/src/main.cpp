#include "light_detector/light_detector.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    //====== 1.处理命令行所传入的参数 ======
    if (argc < 3)
    {
        std::cerr << "用法: " << argv[0] << " <图像路径> <阈值>" << std::endl;
        return -1;
    }

    std::string image_path = argv[1];
    int binary_thres = std::stoi(argv[2]); // 转换为 int

    cv::Mat bgr_img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (bgr_img.empty())
    {
        std::cerr << "error " << image_path << std::endl;
        return -1;
    }
    std::cout << "1. bgr image read " << std::endl;

    // ====== 2.初始化一个Detector对象 ======
    Detector detector;
    std::cout << "2. Detector Initialized!" << std::endl;

    // ====== 3.预处理图像：灰度化 -> 二值化 ======

    // ====== 4.提取轮廓 ======

    // ====== 5.绘制轮廓 ======
    detector.drawContours(bgr_img, contours);
    std::cout << "5. drawContours finished " << std::endl;

    return 0;
}