#ifndef LIGHT_DETECTOR_HPP
#define LIGHT_DETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <vector>

class Detector
{
public:
    Detector();
    ~Detector();

    // 检查detect_color  RED-0 BLUE-0
    bool checkColor(const cv::Mat &bgr_img, int detect_color);

    // 图像预处理：彩色图像转灰度图，然后进行二值化
    cv::Mat preprocessImage(const cv::Mat &bgr_img, int binary_thres);

    // 提取图像中的轮廓
    std::vector<std::vector<cv::Point>> findContoursInBinary(const cv::Mat &binary_img);

    // 在原始图像上绘制提取到的轮廓
    void drawContours(cv::Mat &bgr_img, const std::vector<std::vector<cv::Point>> &contours);

private:
    // 成员变量（如果需要，目前没有特定需求）
};

#endif // LIGHT_DETECTOR_HPP