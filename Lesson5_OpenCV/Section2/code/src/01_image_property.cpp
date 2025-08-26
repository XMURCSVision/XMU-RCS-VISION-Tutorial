#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

void get_properties(const cv::Mat &image)
{
    if (image.empty())
    {
        std::cout << "[图像为空] 无法获取属性！" << std::endl;
        return;
    }

    int width = image.cols;
    int height = image.rows;
    int channels = image.channels();
    int type = image.type();
    int depth = CV_MAT_DEPTH(type);
    int totalPixels = image.total();

    std::cout << "====== 图像属性 ======" << std::endl;
    std::cout << "尺寸（宽 x 高）   : " << width << " x " << height << std::endl;
    std::cout << "通道数           : " << channels << std::endl;
    std::cout << "类型（type）     : " << type << std::endl;
    std::cout << "深度（depth）    : " << depth << " （" << image.depth() << "）" << std::endl;
    std::cout << "总像素点数       : " << totalPixels << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << std::endl;
}

int main()
{
    cv::Mat image_gray = cv::imread("../../images/deepsleep.jpg", cv::IMREAD_COLOR);
    cv::Mat image_color = cv::imread("../../images/deepsleep.jpg", cv::IMREAD_GRAYSCALE);

    // 获取图像属性
    get_properties(image_gray);
    get_properties(image_color);

    // 显示图像
    cv::imshow("Gray Image", image_gray);
    cv::imshow("Modified Color Image", image_color);

    std::cout << "按 ESC 键关闭所有窗口\n";
    while (true)
    {
        int key = cv::waitKey(0);
        if (key == 27) // ESC键
            break;
    }
    cv::destroyAllWindows();

    return 0;
}