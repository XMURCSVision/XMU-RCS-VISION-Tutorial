#include "detector/light_detector.hpp"
#include <iostream>

Detector::Detector()
{
    // 构造函数，无需初始化特定参数
}

Detector::~Detector()
{
    // 析构函数，无需特定清理
}

bool Detector::checkColor(const cv::Mat &bgr_img, int detect_color)
{
    // 思路提示：
    // 获取图像中B(sum_blue)和R(sum_red)像素值的总和
    // 在detect_color == 0时，如果sum_red>sum_blue,为正常返回True,否则False
}

cv::Mat Detector::preprocessImage(const cv::Mat &bgr_img, int binary_thres)
{
    cv::Mat gray_img;
    // 将BGR图像（OpenCV imread默认读取）转换为灰度图像
    cv::cvtColor(bgr_img, gray_img, cv::COLOR_BGR2GRAY);

    cv::Mat binary_img;
    // 使用传入的阈值进行二值化
    cv::threshold(gray_img, binary_img, binary_thres, 255, cv::THRESH_BINARY);

    // 显示二值化图像
    cv::imshow("Binary Image", binary_img);
    cv::waitKey(1);

    return binary_img;
}

std::vector<std::vector<cv::Point>> Detector::findContoursInBinary(const cv::Mat &binary_img)
{
    std::vector<std::vector<cv::Point>> contours; // 轮廓容器
    std::vector<cv::Vec4i> hierarchy;             // 层次结构（此示例中不需要，但findContours需要）

    // 查找图像中的所有外部轮廓
    // cv::RETR_EXTERNAL: 只检索外部轮廓
    // cv::CHAIN_APPROX_SIMPLE: 压缩水平、垂直和对角线段，只保留它们的端点
    cv::findContours(binary_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 返回所有找到的轮廓
    return contours;
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
    cv::imshow("Contours", output_img);
    cv::waitKey(0); // 等待按键，直到窗口关闭
}