#include "light_detector/light_detector.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    //====== 1.处理命令行所传入的参数 ======
    // 检查参数数量
    if (argc < 3)
    {
        std::cerr << "用法: " << argv[0] << " <图像路径> <阈值>" << std::endl;
        return -1;
    }

    // 读取图像路径和阈值参数
    std::string image_path = argv[1];
    int binary_thres = std::stoi(argv[2]); // 转换为 int

    // 读取图像
    cv::Mat bgr_img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (bgr_img.empty())
    {
        std::cerr << "无法读取图像: " << image_path << std::endl;
        return -1;
    }
    std::cout << "1. 图像加载成功。" << std::endl;

    // ====== 2.初始化一个Detector对象 ======
    Detector detector; // 在栈上创建Detector对象
    std::cout << "2. Detector对象初始化成功。" << std::endl;

    // ====== 3.预处理图像：灰度化 -> 二值化 ======
    auto binary_img = detector.preprocessImage(bgr_img, binary_thres);
    std::cout << "3. 图像预处理完成（灰度化和二值化）。" << std::endl;

    // ====== 4.提取轮廓 ======
    auto contours = detector.findContoursInBinary(binary_img);
    std::cout << "4. 提取到轮廓数量: " << contours.size() << std::endl;

    // ====== 5.绘制轮廓 ======
    detector.drawContours(bgr_img, contours);
    std::cout << "5. 轮廓绘制完成，显示结果。" << std::endl;

    return 0;
}