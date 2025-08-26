#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat image_gray = cv::imread("../../images/deepsleep.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat image_color = cv::imread("../../images/deepsleep.jpg", cv::IMREAD_COLOR);

    // 1. 获取图像的属性
    int width = image_color.cols;
    int height = image_color.rows;
    int channels = image_color.channels();
    int type = image_color.type();
    int depth = CV_MAT_DEPTH(type);
    int totalPixels = image_color.total();

    // 2.读取并修改灰度图（100,100）像素点的像素值
    uchar gray_value = image_gray.at<uchar>(100, 100); // 读取
    cout << "gray value is :" << static_cast<int>(gray_value) << endl;
    image_gray.at<uchar>(100, 100) = 255; // 修改为255，即白色

    // 3.读取并修改BGR图（100,100）像素点的像素值
    cv::Vec3b bgr_pixel = image_color.at<cv::Vec3b>(100, 100);
    std::cout << "bgr value is : ("
              << static_cast<int>(bgr_pixel[0]) << ", "
              << static_cast<int>(bgr_pixel[1]) << ", "
              << static_cast<int>(bgr_pixel[2]) << ")" << std::endl;

    // 将该像素设为绿色 (B=0, G=255, R=0)
    bgr_pixel[0] = 0;   // B通道
    bgr_pixel[1] = 255; // G通道
    bgr_pixel[2] = 0;   // R通道
    image_color.at<cv::Vec3b>(100, 100) = bgr_pixel;

    // 4. 显示图像
    cv::imshow("Modified Gray Image", image_gray);
    cv::imshow("Modified Color Image", image_color);

    std::cout << "按 ESC 键关闭所有窗口\n";
    while (true)
    {
        int key = cv::waitKey(0);
        if (key == 27) // ESC键
            break;
    }
    cv::destroyAllWindows();

    // 5. 保存修改后的图像
    cv::imwrite("../../images/gray_modified.jpg", image_gray);
    cv::imwrite("../../images/color_modified.jpg", image_color);

    return 0;
}