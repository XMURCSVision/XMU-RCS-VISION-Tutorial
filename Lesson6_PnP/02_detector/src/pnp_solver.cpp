#include "pnp_solver.hpp"
#include "armor.hpp"

#include <iostream>
#include <algorithm>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

PnpSolver::PnpSolver()
{
    std::cout << "PnpSolver: Initialized." << std::endl;
}

// 👇 新增：从 main 传入相机参数
void PnpSolver::setCameraParams(const cv::Mat &camera_matrix, const cv::Mat &dist_coeffs)
{
    camera_matrix_ = camera_matrix.clone();
    dist_coeffs_ = dist_coeffs.clone();
}

// 对角点排序，确保与3D模型对应
void PnpSolver::sortPointsForPnP(std::vector<cv::Point2f> &points)
{
    std::sort(points.begin(), points.end(), [](const cv::Point2f &a, const cv::Point2f &b)
              {
                  if (std::abs(a.y - b.y) < 5)
                      return a.x < b.x;
                  return a.y < b.y; });

    if (points[0].x > points[1].x)
        std::swap(points[0], points[1]);
    if (points[2].x > points[3].x)
        std::swap(points[2], points[3]);

    std::vector<cv::Point2f> sorted(4);
    sorted[0] = points[0]; // 左上
    sorted[1] = points[1]; // 右上
    sorted[2] = points[3]; // 右下
    sorted[3] = points[2]; // 左下

    points = sorted;
}

// 提取灯条并返回装甲板四个角点
std::vector<cv::Point2f> PnpSolver::obtain2DCorners(const std::vector<std::vector<cv::Point>> &all_raw_contours)
{
    std::vector<cv::Point2f> image_points;

    std::vector<cv::RotatedRect> light_bar_rects;
    for (const auto &contour : all_raw_contours)
    {
        if (contour.size() < 5)
            continue;

        cv::RotatedRect rect = cv::minAreaRect(contour);
        double area = rect.size.area();
        double aspect_ratio = rect.size.width / rect.size.height;
        if (aspect_ratio < 1)
            aspect_ratio = 1.0 / aspect_ratio;

        if (area > 100 && area < 10000 && aspect_ratio > 2.0 && aspect_ratio < 10.0)
        {
            light_bar_rects.push_back(rect);
        }
    }

    if (light_bar_rects.size() < 2)
    {
        std::cout << "PnpSolver::obtain2DCorners: Not enough valid light bars." << std::endl;
        return {};
    }

    if (light_bar_rects.size() > 2)
    {
        std::sort(light_bar_rects.begin(), light_bar_rects.end(),
                  [](const cv::RotatedRect &a, const cv::RotatedRect &b)
                  {
                      return a.size.area() > b.size.area();
                  });
        light_bar_rects.resize(2);
    }

    std::vector<cv::Point2f> all_light_points;
    cv::Point2f pts[4];

    light_bar_rects[0].points(pts);
    for (int i = 0; i < 4; ++i)
        all_light_points.push_back(pts[i]);

    light_bar_rects[1].points(pts);
    for (int i = 0; i < 4; ++i)
        all_light_points.push_back(pts[i]);

    if (all_light_points.empty())
        return {};

    cv::RotatedRect armor_rect = cv::minAreaRect(all_light_points);
    cv::Point2f corners[4];
    armor_rect.points(corners);

    image_points.assign(corners, corners + 4);

    if (image_points.size() == 4)
        sortPointsForPnP(image_points);
    else
        return {};

    return image_points;
}

// 获取 3D 世界坐标点（调用装甲板参数）
std::vector<cv::Point3f> PnpSolver::obtain3DCorners(const Armor_params &armor_physical_params)
{
    return armor_physical_params.object_points;
}

// 执行 PnP 求解
bool PnpSolver::solvePnP(const std::vector<cv::Point3f> &object_points,
                         const std::vector<cv::Point2f> &image_points,
                         cv::Mat &rvec_out,
                         cv::Mat &tvec_out)
{
    if (image_points.size() != object_points.size() || image_points.size() < 4)
    {
        std::cerr << "PnP Error: Insufficient point pairs." << std::endl;
        return false;
    }

    if (camera_matrix_.empty() || dist_coeffs_.empty())
    {
        std::cerr << "PnP Error: Camera parameters not set." << std::endl;
        return false;
    }

    bool success = cv::solvePnP(object_points, image_points, camera_matrix_, dist_coeffs_,
                                rvec_out, tvec_out, false, cv::SOLVEPNP_ITERATIVE);

    if (success)
        std::cout << "PnP solve success." << std::endl;
    else
        std::cerr << "PnP solve failed." << std::endl;

    return success;
}
