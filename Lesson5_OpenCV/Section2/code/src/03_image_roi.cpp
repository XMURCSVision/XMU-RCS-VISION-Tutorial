#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int main()
{
    cv::Mat image = cv::imread("../../images/deepsleep.jpg", cv::IMREAD_GRAYSCALE);

    // 1.示例一 从 (50, 50) 开始，宽100，高100的矩形区域
    cv::Rect roi_1(50, 50, 100, 100);  // 从 (50, 50) 开始，宽100，高100的矩形区域
    cv::Mat imageROI_1 = image(roi_1); // 裁剪 ROI 区域

    // 2.示例二 截取正中间的 ROI（尺寸为原图 1/2 × 1/2）
    int width = image.cols;
    int height = image.rows;

    int roi_w = width / 2;
    int roi_h = height / 2;
    int roi_x = (width - roi_w) / 2;
    int roi_y = (height - roi_h) / 2;
    cv::Rect roi_center(roi_x, roi_y, roi_w, roi_h);
    cv::Mat image_ROI_center = image(roi_center).clone(); // clone 复制

    // 显示图像
    cv::imshow("Original image", image);
    cv::imshow("ROI_1", imageROI_1);
    cv::imshow("ROI_center", image_ROI_center);

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