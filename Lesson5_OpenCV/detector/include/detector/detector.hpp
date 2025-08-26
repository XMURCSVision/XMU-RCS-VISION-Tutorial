#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "detector/armor.hpp"

class Detector
{
public:
    // ====== 成员函数 ======
    // 构造析构
    Detector();
    ~Detector();

    // 主要函数
    cv::Mat preprocessImage(const cv::Mat &bgr_img, int binary_thres);
    std::vector<Light> findLights(const cv::Mat &bgr_img, const cv::Mat &binary_img);
    std::vector<Armor> matchLights(const std::vector<Light> &lights, int detect_color);

    // 辅助函数
    bool isLight(const Light &light);
    bool containLight(
        const Light &light_1, const Light &light_2, const std::vector<Light> &lights);

    // 绘图
    void drawResults(cv::Mat &bgr_img, std::vector<Light> lights_, std::vector<Armor> armors_);

    // 设置私有成员变量
    void setValue(const std::vector<Light> &lights_, const std::vector<Armor> &armors_);

    // ====== 成员变量 ====== 请问用在哪里了？
    // 灯条参数
    struct LightParams
    {
        // width / height
        double min_ratio; // 最小宽高比
        double max_ratio; // 最大宽高比
        // vertical angle
        double max_angle; // 最大垂直角
    };

    // 装甲板参数
    struct ArmorParams
    {
        double min_light_ratio;
        // light pairs distance
        double min_small_center_distance; // 小装甲板中，最小的
        double max_small_center_distance;
        double min_large_center_distance;
        double max_large_center_distance;
        // horizontal angle
        double max_angle;
    };
    /*注：装甲板有分大小装甲板，示例中仅使用了小装甲板，于是Params结构体中都只写了小装甲板参数*/

    LightParams l;
    ArmorParams a;

private:
    std::vector<Light> lights_;
    std::vector<Armor> armors_;
    /* 注：实际情况中，一帧图像里可能会看到4个灯条/2组装甲板，
    虽然示例图都是一个装甲板，但是为了维护规范，使用vector */
};

#endif