// Copyright 2022 Chen Jun

//已注释
//疑问：object_points和 image_armor_points是？？
//image_armor_points是图像的(u,v)坐标  -->图像处理后得出
//object_points是空间位置坐标(x,y,z) (相对于世界坐标系)(世界坐标系原点为装甲板中心点)-->固定数值直接填

//PnP解算的目的是?? 算出R和t

//(u,v)坐标是在哪里处理的??

#include "armor_detector/pnp_solver.hpp"

#include <opencv2/calib3d.hpp>
#include <vector>

namespace rm_auto_aim
{
PnPSolver::PnPSolver(
  const std::array<double, 9> & camera_matrix, const std::vector<double> & dist_coeffs)
: camera_matrix_(cv::Mat(3, 3, CV_64F, const_cast<double *>(camera_matrix.data())).clone()),
  dist_coeffs_(cv::Mat(1, 5, CV_64F, const_cast<double *>(dist_coeffs.data())).clone())
  //:后面是初始化成员列表
  //以初始化camera_matirx_成员变量为例：
  //cv::Mat(3,3,CV_64F,const_cast<double *>()) 创建一个3*3 cv::Mat 成员对象，
  //数据类型为double，来源为camera_matrix，通过.clone()方法创建一个副本，并赋值给camera_matrix_

{
  // Unit: m
  //小装甲板 y的一半 为 宽度/2 再单位换算mm->m
  constexpr double small_half_y = SMALL_ARMOR_WIDTH / 2.0 / 1000.0;  
  constexpr double small_half_z = SMALL_ARMOR_HEIGHT / 2.0 / 1000.0;
  constexpr double large_half_y = LARGE_ARMOR_WIDTH / 2.0 / 1000.0;
  constexpr double large_half_z = LARGE_ARMOR_HEIGHT / 2.0 / 1000.0;

  // Start from bottom left in clockwise order
  //从左下 顺时针方向
  // Model coordinate: x forward, y left, z up
  //右手系：x前 y左 z上
  //3D-2D需一一对应
  //以装甲板中心为原点，x一定是0，yz会产生正负，值均为half
  small_armor_points_.emplace_back(cv::Point3f(0, small_half_y, -small_half_z));
  small_armor_points_.emplace_back(cv::Point3f(0, small_half_y, small_half_z));
  small_armor_points_.emplace_back(cv::Point3f(0, -small_half_y, small_half_z));
  small_armor_points_.emplace_back(cv::Point3f(0, -small_half_y, -small_half_z));

  large_armor_points_.emplace_back(cv::Point3f(0, large_half_y, -large_half_z));
  large_armor_points_.emplace_back(cv::Point3f(0, large_half_y, large_half_z));
  large_armor_points_.emplace_back(cv::Point3f(0, -large_half_y, large_half_z));
  large_armor_points_.emplace_back(cv::Point3f(0, -large_half_y, -large_half_z));
}

bool PnPSolver::solvePnP(const Armor & armor, cv::Mat & rvec, cv::Mat & tvec)
{
  std::vector<cv::Point2f> image_armor_points;  //std::vector容器 用于存储cv::Point2f型数据 名称为image_armor_points

  // Fill in image points
  //emplace_back在末尾添加，从左下开始顺时针
  image_armor_points.emplace_back(armor.left_light.bottom);
  image_armor_points.emplace_back(armor.left_light.top);
  image_armor_points.emplace_back(armor.right_light.top);
  image_armor_points.emplace_back(armor.right_light.bottom);

  // Solve pnp
  auto object_points = armor.type == ArmorType::SMALL ? small_armor_points_ : large_armor_points_;  
  //判断装甲板类型：大装甲板or小装甲板
  //使用自动类型推导，赋值为 std::vector<cv::Point3f>型 （在hpp中定义）
  
  //自定义的bool bool PnPSolver::solvePnP(,)函数，其返回值为 cv::solvePnP的返回值，找到了就返回true
  return cv::solvePnP(
    object_points, image_armor_points, camera_matrix_, dist_coeffs_, rvec, tvec, false,
    cv::SOLVEPNP_IPPE);  
    //hpp中有自定义的bool型函数solvePnP，这里cv::solvePnP 是OpenCV库函数
    /*函数原型如下：
    bool cv::solvePnP(
        const cv::Mat& objectPoints,  //一个vector<cv::Point3f> 至少需要4个点
        const cv::Mat& imagePoints,   //一个vector<cv::Point2f> 与上面的objectPoints的点一一对应
        const cv::Mat& cameraMatrix,  //相机内参矩阵3*3
        const cv::Mat& distCoeffs,    //畸变系数 1*5
        cv::Mat& rvec,   //输出的R 类型为cv::Mat
        cv::Mat& tvec,   //输出的t 类型为cv::Mat
        bool useExtrinsicGuess = false,   //表示是否使用可选的旋转和平移向量的初始猜测，默认为 false
        int flags = cv::SOLVEPNP_ITERATIVE )  //一个用于控制函数行为的选项标志，默认为 0
    如果函数成功地找到了相机姿态，cv::solvePnP会返回true，否则false
    */
}

float PnPSolver::calculateDistanceToCenter(const cv::Point2f & image_point)  
{
  float cx = camera_matrix_.at<double>(0, 2);  
  float cy = camera_matrix_.at<double>(1, 2);  
  //从内参矩阵中把cx提取出来
  //.at<T>(row, col)是cv::Mat类的一个成员函数，返回指定位置（行、列索引）的元素的引用
  
  return cv::norm(image_point - cv::Point2f(cx, cy));  
  //传参传入了cv::Point2f image_point 求image_point和（cx，cy）间的距离
}

}  // namespace rm_auto_aim
