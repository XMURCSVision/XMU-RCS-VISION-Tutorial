// Copyright 2022 Chen Jun
// Licensed under the MIT License.

// 已注释

#ifndef ARMOR_DETECTOR__ARMOR_HPP_
#define ARMOR_DETECTOR__ARMOR_HPP_

#include <opencv2/core.hpp>

// STL
#include <algorithm>
#include <string>

namespace rm_auto_aim
{
  const int RED = 0;
  const int BLUE = 1;

  enum class ArmorType
  {
    SMALL,
    LARGE,
    INVALID
  }; // 枚举类型 小、大、无效（无效是指我方吗？）
  const std::string ARMOR_TYPE_STR[3] = {"small", "large", "invalid"};

  // 灯条结构体 struct默认是publi
  struct Light : public cv::RotatedRect // cv::RotatedRect是旋转的矩形，其中可以包含矩形的中心点、尺寸和旋转角度
  {
    Light() = default;

    explicit Light(cv::RotatedRect box) : cv::RotatedRect(box)
    // 参数列表：接收一个cv::RotatedRect型的box变量
    // 初始化列表：Light的基类部分cv::RotatedRect会被初始化为box
    {
      cv::Point2f p[4]; // cv::Point2f类的一个数组，用于存四个点坐标
      // cv::Point2f p(1.0f, 2.0f); // 初始化一个二维点，坐标为 (1.0, 2.0)

      box.points(p); // points是cv::RotatedRect的一个成员函数，用于获得旋转矩形的四个顶点

      std::sort(p, p + 4, [](const cv::Point2f &a, const cv::Point2f &b)
                { return a.y < b.y; });
      // 标准库中的数组排序函数，起始指针p，结束指针p+4
      // 第三个参数是Lambda表达式，用作排序的比较函数，返回值是bool型，小的点为p[0]

      top = (p[0] + p[1]) / 2; // top定义是cv::Point2f型  //上方长边中点
      bottom = (p[2] + p[3]) / 2;

      length = cv::norm(top - bottom); // 高
      width = cv::norm(p[0] - p[1]);   // 宽

      tilt_angle = std::atan2(std::abs(top.x - bottom.x), std::abs(top.y - bottom.y));
      // 倾斜角度 弧度制
      // atan即arctan  arctan(y1-y2/x1-x2)

      tilt_angle = tilt_angle / CV_PI * 180;
      // 弧度转角度
    }

    int color;
    cv::Point2f top, bottom;
    double length;
    double width;
    float tilt_angle;
  };

  // 装甲板结构体
  struct Armor
  {
    Armor() = default; // 默认构造函数，成员变量会默认初始化
    Armor(const Light &l1, const Light &l2)
    {
      // 左右灯条判断
      // center是cv::RotatedRect::center的成员函数，返回值为rectangle mass center矩形质心
      if (l1.center.x < l2.center.x)
      {
        left_light = l1, right_light = l2;
      }
      else
      {
        left_light = l2, right_light = l1;
      }

      // 装甲板中心点 由 左右灯条中心点 求中点而得
      center = (left_light.center + right_light.center) / 2;
    }

    // Light pairs part
    Light left_light, right_light;
    cv::Point2f center; // cv::Point2f型变量center
    ArmorType type;     // 我自己的装甲板？？敌我识别？

    // Number part
    cv::Mat number_img; // cv::Mat类，用于图像和矩阵
    std::string number;
    float confidence;
    std::string classfication_result;
  };

} // namespace rm_auto_aim

#endif // ARMOR_DETECTOR__ARMOR_HPP_
