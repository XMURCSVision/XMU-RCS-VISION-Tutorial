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
    if (bgr_img.empty())
    {
        std::cerr << "ERROR: Input image is empty, cannot check color!" << std::endl;
        return false;
    }

    // 计算图像中红色和蓝色通道的总像素值
    long long sum_red = 0;
    long long sum_blue = 0;

    // 遍历图像的每个像素
    for (int i = 0; i < bgr_img.rows; i++)
    {
        const cv::Vec3b *pixel_row = bgr_img.ptr<cv::Vec3b>(i); // 获取行指针，提高效率
        for (int j = 0; j < bgr_img.cols; j++)
        {
            // OpenCV的Vec3b存储顺序是BGR
            sum_blue += pixel_row[j][0]; // 蓝色通道
            // pixel_row[j][1] 是绿色通道
            sum_red += pixel_row[j][2]; // 红色通道
        }
    }

    // 打印红蓝像素总和
    std::cout << "DEBUG: Total Red Pixels Sum: " << sum_red << std::endl;
    std::cout << "DEBUG: Total Blue Pixels Sum: " << sum_blue << std::endl;

    // 根据 detect_color 参数进行判断
    if (detect_color == 0)
    { // 检测红色
        if (sum_red > sum_blue)
        {
            return true; // 红色总数大于蓝色，符合要求
        }
        else
        {
            return false; // 不符合红色要求
        }
    }
    else if (detect_color == 1)
    { // 检测蓝色
        if (sum_blue > sum_red)
        {
            return true; // 蓝色总数大于红色，符合要求
        }
        else
        {
            return false; // 不符合蓝色要求
        }
    }
    else
    {
        std::cerr << "ERROR: Invalid detect_color parameter! Please use 0 (Red) or 1 (Blue)." << std::endl;
        return false; // 无效的 detect_color
    }
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