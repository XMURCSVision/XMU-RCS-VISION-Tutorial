// Copyright 2022 Chen Jun
// Licensed under the MIT License.

//已注释

#ifndef ARMOR_DETECTOR__PNP_SOLVER_HPP_
#define ARMOR_DETECTOR__PNP_SOLVER_HPP_

#include <geometry_msgs/msg/point.hpp>
#include <opencv2/core.hpp>

// STD
#include <array>  //array是固定大小的数组
#include <vector>  //vector是动态数组容器

#include "armor_detector/armor.hpp"

namespace rm_auto_aim
{
class PnPSolver
{
public:
  PnPSolver(
    const std::array<double, 9> & camera_matrix,  //相机内参
    const std::vector<double> & distortion_coefficients);  //畸变系数

  // Get 3d position
  bool solvePnP(const Armor & armor, cv::Mat & rvec, cv::Mat & tvec);

  // Calculate the distance between armor center and image center
  float calculateDistanceToCenter(const cv::Point2f & image_point);

private:
  cv::Mat camera_matrix_;
  cv::Mat dist_coeffs_;

  // Unit: mm
  //大装甲板、小装甲板 高、宽
  static constexpr float SMALL_ARMOR_WIDTH = 135;  //constexpr关键字：允许编译器在编译时计算表达式的值，而不是在运行时
  static constexpr float SMALL_ARMOR_HEIGHT = 55;
  static constexpr float LARGE_ARMOR_WIDTH = 225;
  static constexpr float LARGE_ARMOR_HEIGHT = 55;

  // Four vertices of armor in 3d
  //顶点
  std::vector<cv::Point3f> small_armor_points_;
  std::vector<cv::Point3f> large_armor_points_;
};

}  // namespace rm_auto_aim

#endif  // ARMOR_DETECTOR__PNP_SOLVER_HPP_
