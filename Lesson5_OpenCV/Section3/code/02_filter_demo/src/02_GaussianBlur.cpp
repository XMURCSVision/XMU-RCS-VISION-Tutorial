#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    // 1. 处理命令行参数
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <ksize> <sigmaX> [sigmaY]" << std::endl;
        std::cerr << "Example: " << argv[0] << " input.jpg 5 1.5" << std::endl;
        return -1;
    }

    // 读取图像
    cv::Mat src = cv::imread(argv[1]);
    if (src.empty())
    {
        std::cerr << "Error: Could not load image!" << std::endl;
        return -1;
    }

    // 2. 转换参数（确保ksize是正奇数，sigma非负）
    int ksize = std::stoi(argv[2]);
    double sigmaX = std::stod(argv[3]);
    double sigmaY = (argc >= 5) ? std::stod(argv[4]) : 0; // 可选参数

    if (ksize <= 0 || ksize % 2 == 0)
    {
        std::cerr << "Error: ksize must be a positive odd number!" << std::endl;
        return -1;
    }
    if (sigmaX < 0 || sigmaY < 0)
    {
        std::cerr << "Error: sigma values must be non-negative!" << std::endl;
        return -1;
    }

    // 3. 创建输出图像
    cv::Mat dst;

    // 4. 应用高斯模糊
    cv::GaussianBlur(src, dst, cv::Size(ksize, ksize), sigmaX, sigmaY);

    // 5. 显示结果
    cv::imshow("Original Image", src);
    cv::imshow("Gaussian Blurred Image", dst);

    // 6. 保存结果（可选）
    cv::imwrite("../output/gaussian_blurred.jpg", dst);

    // 7. 等待按键退出
    cv::waitKey(0);
    return 0;
}