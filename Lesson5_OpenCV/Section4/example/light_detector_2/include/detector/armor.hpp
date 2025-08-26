#ifndef ARMOR_HPP
#define ARMOR_HPP

#include <vector>
#include <opencv2/core.hpp> // 包含cv::Point2f等OpenCV基本类型

// 装甲板结构体
struct Armor
{
    // 原始的灯条轮廓，通常是像素坐标
    std::vector<std::vector<cv::Point>> light_bar_contours;

    // 这些是PnP解算所需的图像2D点（共4个灯条角点）
    std::vector<cv::Point2f> image_points;

    // PnP解算结果
    cv::Mat rvec; // 旋转向量
    cv::Mat tvec; // 平移向量

    // 其他可能需要的成员：
    // cv::Rect bounding_box; // 装甲板的最小外接矩形
    // cv::Point2f center; // 装甲板在图像中的中心点
};

// 装甲板尺寸等参数
struct Armor_params
{
    // 装甲板的实际物理尺寸 (长和宽，单位m)
    double armor_width;
    double armor_height;

    // 灯条的物理尺寸
    double light_bar_width;
    double light_bar_height;

    // 灯条在装甲板上的相对位置信息
    // 例如，两个灯条中心点之间的距离，或者用于构建3D点时的偏移量
    // 这个取决于你如何定义装甲板的3D模型
    double light_bar_spacing; // 灯条间距

    // PnP解算所需的3D世界点（物体点）
    // 这个在初始化时根据上面的尺寸计算一次即可
    std::vector<cv::Point3f> object_points;

    // 构造函数，方便初始化并计算object_points
    Armor_params(double a_w, double a_h, double lb_w, double lb_h, double lb_s)
        : armor_width(a_w), armor_height(a_h),
          light_bar_width(lb_w), light_bar_height(lb_h),
          light_bar_spacing(lb_s)
    {
        // 根据装甲板中心为原点，计算四个角点的3D坐标
        // 假设装甲板是平面，Z坐标为0
        object_points.emplace_back(-armor_width / 2.0, armor_height / 2.0, 0.0);
        object_points.emplace_back(armor_width / 2.0, armor_height / 2.0, 0.0);
        object_points.emplace_back(armor_width / 2.0, -armor_height / 2.0, 0.0);
        object_points.emplace_back(-armor_width / 2.0, -armor_height / 2.0, 0.0);
    }
};

#endif // ARMOR_HPP