#include "detector/light_detector.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    //====== 1.处理命令行所传入的参数 ======
    // 检查参数数量：图像路径、阈值、检测颜色
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold> <detect_color (0:Red, 1:Blue)>" << std::endl;
        return -1;
    }

    // 读取图像路径、阈值和检测颜色参数
    std::string image_path = argv[1];
    int binary_thres = std::stoi(argv[2]); // 转换为 int
    int detect_color = std::stoi(argv[3]); // 检测颜色：0代表红色，1代表蓝色

    // 读取图像
    cv::Mat bgr_img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (bgr_img.empty())
    {
        std::cerr << "ERROR: Could not read image from: " << image_path << std::endl;
        return -1;
    }
    std::cout << "1. Image loaded successfully." << std::endl;

    // ====== 2.初始化一个Detector对象 ======
    Detector detector; // 在栈上创建Detector对象
    std::cout << "2. Detector object initialized." << std::endl;

    // ====== 3.检查图像颜色是否符合要求 ======
    if (!detector.checkColor(bgr_img, detect_color))
    {
        std::cout << "Invalid" << std::endl; // 不符合颜色要求，打印"Invalid"
        return 0;                            // 不符合则直接退出程序
    }
    std::cout << "3. Image color meets requirement, proceeding with processing." << std::endl;

    // ====== 4.预处理图像：灰度化 -> 二值化 ======
    auto binary_img = detector.preprocessImage(bgr_img, binary_thres);
    std::cout << "4. Image preprocessed (grayscale and binary)." << std::endl;

    // ====== 5.提取轮廓 ======
    auto light_bar_contours = detector.findContoursInBinary(binary_img);
    std::cout << "5. Number of contours found: " << light_bar_contours.size() << std::endl;

    // ====== 6.绘制轮廓 ======
    detector.drawContours(bgr_img, light_bar_contours);
    std::cout << "6. Contour drawing complete, displaying results." << std::endl;

    return 0;
}