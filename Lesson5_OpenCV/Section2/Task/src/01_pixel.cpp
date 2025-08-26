// task_2.cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 1. 读取图像
    cv::Mat image = cv::imread("../images/task_1.jpg");
    if (image.empty())
    {
        std::cerr << "error ../images/task_1.jpg" << std::endl;
        return -1;
    }

    // 2. 检查图像是否为彩色图 (3通道)
    if (image.channels() != 3)
    {
        std::cerr << "错误: 该任务需要一张彩色图像。" << std::endl;
        return -1;
    }

    // 3. 计算图像的几何中心点坐标
    int centerX = image.cols / 2;
    int centerY = image.rows / 2;

    // 4. 获取中心点的像素值
    // cv::Mat::at 的参数顺序是 (row, col)，即 (y, x)
    // cv::Vec3b 是一个包含3个 uchar 成员的向量，用于表示BGR像素
    cv::Vec3b pixelValue = image.at<cv::Vec3b>(centerY, centerX);

    // 5. 提取 B, G, R 通道的值
    uchar blue = pixelValue[0];
    uchar green = pixelValue[1];
    uchar red = pixelValue[2];

    // 6. 打印像素值
    // 使用 static_cast<int> 是为了确保 uchar 类型的值被当作整数打印，而不是字符
    std::cout << "Size of the image: " << image.cols << "x" << image.rows << std::endl;
    std::cout << "Center: (" << centerX << ", " << centerY << ")" << std::endl;
    std::cout << "BGR: ["
              << static_cast<int>(blue) << ", "
              << static_cast<int>(green) << ", "
              << static_cast<int>(red) << "]" << std::endl;

    // 7. 显示图像
    cv::imshow("Task2_center", image);

    // 8. 等待按键后退出
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}