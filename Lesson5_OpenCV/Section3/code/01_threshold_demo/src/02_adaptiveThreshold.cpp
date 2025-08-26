#include <opencv2/opencv.hpp> // 包含OpenCV库
#include <iostream>           // 包含输入输出流库
#include <string>             // 包含字符串库

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold>" << std::endl;
        return -1;
    }

    std::string image_path = argv[1];
    int binary_threshold = std::stoi(argv[2]);

    cv::Mat src = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

    if (src.empty())
    {
        std::cerr << "ERROR: Could not read image from: " << image_path << std::endl;
        return -1; // 图像读取失败，退出程序
    }

    cv::imshow("Original Gray Image", src);

    cv::Mat dst;

    // 应用自适应阈值
    adaptiveThreshold(src, dst, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);

    cv::imshow("Binary Image", dst);

    cv::waitKey(0);

    return 0; // 程序成功执行
}