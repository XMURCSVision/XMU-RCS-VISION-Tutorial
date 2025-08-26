// task_3.cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main()
{
    // 1. 读取图像
    cv::Mat image = cv::imread("../images/task_2.jpg");
    if (image.empty())
    {
        std::cerr << "error ../images/task_3.jpg" << std::endl;
        return -1;
    }

    // --- 任务 3.1: 将 R 通道值设为 255 ---
    cv::Mat image_red_255 = image.clone(); // 创建副本进行操作
    std::vector<cv::Mat> channels_r;
    cv::split(image_red_255, channels_r);
    // BGR 顺序中，红色通道是第2个索引 (channels_r[2])
    channels_r[2] = cv::Mat(image.size(), CV_8UC1, cv::Scalar(255));
    // 更简洁的写法: channels_r[2].setTo(cv::Scalar(255));
    cv::merge(channels_r, image_red_255);
    std::cout << "Red = 255" << std::endl;

    // 2. 显示所有图像
    cv::imshow("原始图像", image);
    cv::imshow("R = 255", image_red_255);

    // 3. 保存结果
    cv::imwrite("../output/task_3_red_255.jpg", image_red_255);
    std::cout << "task_3 saved" << std::endl;

    // 4. 等待按键后退出
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}