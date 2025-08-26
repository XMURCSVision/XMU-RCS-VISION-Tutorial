#include "light_detector/light_detector.hpp"
#include <iostream>

Detector::Detector()
{
    // 构造函数，无需初始化特定参数
}

Detector::~Detector()
{
    // 析构函数，无需特定清理
}

cv::Mat Detector::preprocessImage(const cv::Mat &rgb_img, int binary_thres)
{
    // 返回值二值化图像
}

std::vector<std::vector<cv::Point>> Detector::findContoursInBinary(const cv::Mat &binary_img)
{
    // 返回轮廓数组
}

void Detector::drawContours(cv::Mat &bgr_img, const std::vector<std::vector<cv::Point>> &contours)
{
    // 复制原始图像，以便在上面绘制，不修改原图（可选）
    cv::Mat output_img = bgr_img.clone();

    // 遍历所有轮廓并绘制它们
    // -1表示绘制所有轮廓
    // cv::Scalar(0, 255, 0) 是绿色
    // 2是线条粗细
    cv::drawContours(output_img, contours, -1, cv::Scalar(0, 255, 0), 2);

    // 显示带有轮廓的图像
    cv::imshow("检测到的轮廓", output_img);
    cv::waitKey(0); // 等待按键，直到窗口关闭
}