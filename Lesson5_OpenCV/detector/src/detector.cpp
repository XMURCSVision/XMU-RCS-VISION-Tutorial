#include "detector/detector.hpp"

Detector::Detector() {}
Detector::~Detector()
{
}

//
cv::Mat Detector::preprocessImage(const cv::Mat &rgb_img, int binary_thres)
{
    cv::Mat gray_img;
    cv::cvtColor(rgb_img, gray_img, cv::COLOR_RGB2GRAY);

    cv::Mat binary_img;
    cv::threshold(gray_img, binary_img, binary_thres, 255, cv::THRESH_BINARY);

    cv::imshow("binary", binary_img);

    return binary_img;
}

std::vector<Light> Detector::findLights(const cv::Mat &rgb_img, const cv::Mat &binary_img)
{
    using std::vector;
    vector<vector<cv::Point>> contours; // 轮廓容器
    vector<cv::Vec4i> hierarchy;
    cv::findContours(binary_img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    vector<Light> lights;

    for (const auto &contour : contours)
    {
        if (contour.size() < 5)
            continue;

        auto r_rect = cv::minAreaRect(contour); // 对一个轮廓进行最小外接矩形拟合
        auto light = Light(r_rect);

        // 没有进这个if
        if (isLight(light))
        {
            std::cout << "if" << std::endl;
            auto rect = light.boundingRect();
            if ( // Avoid assertion failed
                0 <= rect.x && 0 <= rect.width && rect.x + rect.width <= rgb_img.cols && 0 <= rect.y &&
                0 <= rect.height && rect.y + rect.height <= rgb_img.rows)
            {
                int sum_r = 0, sum_b = 0;
                auto roi = rgb_img(rect);
                // Iterate through the ROI
                for (int i = 0; i < roi.rows; i++)
                {
                    for (int j = 0; j < roi.cols; j++)
                    {
                        if (cv::pointPolygonTest(contour, cv::Point2f(j + rect.x, i + rect.y), false) >= 0)
                        {
                            // if point is inside contour
                            sum_b += roi.at<cv::Vec3b>(i, j)[0];
                            sum_r += roi.at<cv::Vec3b>(i, j)[2];
                        }
                    }
                }
                // Sum of red pixels > sum of blue pixels ?
                light.color = sum_r > sum_b ? 0 : 1; // red-0 blue-1
                lights.emplace_back(light);
            }
        }
    }

    return lights;
}

std::vector<Armor> Detector::matchLights(const std::vector<Light> &lights, int detect_color)
{
    std::vector<Armor> armors;

    // Loop all the pairing of lights
    for (auto light_1 = lights.begin(); light_1 != lights.end(); light_1++)
    {
        for (auto light_2 = light_1 + 1; light_2 != lights.end(); light_2++)
        {
            if (light_1->color != detect_color || light_2->color != detect_color)
                continue;

            if (containLight(*light_1, *light_2, lights))
            {
                continue;
            }
            auto armor = Armor(*light_1, *light_2);
            armors.emplace_back(armor);
        }
    }

    return armors;
}

// 辅助函数
bool Detector::isLight(const Light &light)
{
    // The ratio of light (short side / long side)
    float ratio = light.width / light.length;
    bool ratio_ok = l.min_ratio < ratio && ratio < l.max_ratio;

    bool angle_ok = light.tilt_angle < l.max_angle;

    bool is_light = ratio_ok && angle_ok;

    return is_light;
}

bool Detector::containLight(
    const Light &light_1, const Light &light_2, const std::vector<Light> &lights)
{
    auto points = std::vector<cv::Point2f>{light_1.top, light_1.bottom, light_2.top, light_2.bottom};
    auto bounding_rect = cv::boundingRect(points);

    for (const auto &test_light : lights)
    {
        if (test_light.center == light_1.center || test_light.center == light_2.center)
            continue;

        if (
            bounding_rect.contains(test_light.top) || bounding_rect.contains(test_light.bottom) ||
            bounding_rect.contains(test_light.center))
        {
            return true;
        }
    }

    return false;
}

// 绘图
void Detector::drawResults(cv::Mat &bgr_img, std::vector<Light> lights_, std::vector<Armor> armors_)
{
    // Draw Lights
    for (const auto &light : lights_)
    {
        cv::circle(bgr_img, light.top, 3, cv::Scalar(255, 255, 255), 1);
        cv::circle(bgr_img, light.bottom, 3, cv::Scalar(255, 255, 255), 1);
        auto line_color = light.color == 0 ? cv::Scalar(255, 255, 0) : cv::Scalar(255, 0, 255);
        cv::line(bgr_img, light.top, light.bottom, line_color, 1);
    }

    // Draw armors
    for (const auto &armor : armors_)
    {
        cv::line(bgr_img, armor.left_light.top, armor.right_light.bottom, cv::Scalar(0, 255, 0), 2);
        cv::line(bgr_img, armor.left_light.bottom, armor.right_light.top, cv::Scalar(0, 255, 0), 2);
    }

    // Show numbers and confidence
    for (const auto &armor : armors_)
    {
        cv::putText(
            bgr_img, armor.classfication_result, armor.left_light.top, cv::FONT_HERSHEY_SIMPLEX, 0.8,
            cv::Scalar(0, 255, 255), 2);
    }
}

// 设置私有成员变量
void Detector::setValue(const std::vector<Light> &lights_, const std::vector<Armor> &armors_)
{
    this->lights_ = lights_;
    this->armors_ = armors_;
}