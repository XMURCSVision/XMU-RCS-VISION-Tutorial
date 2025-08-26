#pragma once

#include <opencv2/core.hpp>
#include <vector>

struct Armor_params;

class PnpSolver
{
public:
    PnpSolver();

    // 直接设置相机参数
    void setCameraParams(const cv::Mat &camera_matrix, const cv::Mat &dist_coeffs);

    std::vector<cv::Point2f> obtain2DCorners(const std::vector<std::vector<cv::Point>> &all_raw_contours);
    std::vector<cv::Point3f> obtain3DCorners(const Armor_params &armor_physical_params);
    bool solvePnP(const std::vector<cv::Point3f> &object_points,
                  const std::vector<cv::Point2f> &image_points,
                  cv::Mat &rvec_out,
                  cv::Mat &tvec_out);

private:
    void sortPointsForPnP(std::vector<cv::Point2f> &points);

    cv::Mat camera_matrix_;
    cv::Mat dist_coeffs_;
};
