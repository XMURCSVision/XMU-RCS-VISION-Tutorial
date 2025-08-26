#include <stdio.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat image = cv::imread("../../images/deepsleep.jpg", cv::IMREAD_COLOR);

    // 拆分通道
    std::vector<cv::Mat> channels;
    cv::split(image, channels); //

    // 对某个通道进行处理，例如将蓝色通道全置为0
    channels[0] = cv::Mat::zeros(channels[0].size(), channels[0].type());

    // 合并通道
    cv::Mat modifiedImage;
    cv::merge(channels, modifiedImage);

    // 显示图像
    cv::imshow("Original image", image);
    cv::imshow("Modified Image (Blue channel = 0)", modifiedImage);

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