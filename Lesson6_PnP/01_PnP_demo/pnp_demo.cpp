#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

int main()
{
    // 1. 定义三维物体点（单位：米或毫米，需与你图像点对应）
    std::vector<cv::Point3f> objectPoints = {
        {0, 0, 0},
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0}};

    // 2. 对应的二维图像点（像素坐标）
    std::vector<cv::Point2f> imagePoints = {
        {523, 441},
        {600, 440},
        {601, 500},
        {524, 501}};

    // 3. 相机内参矩阵（使用你提供的数据）
    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 2334.43093, 0.0, 790.07101,
                            0.0, 2341.75513, 518.56545,
                            0.0, 0.0, 1.0);

    // 4. 相机畸变系数（使用你提供的数据）
    cv::Mat distCoeffs = (cv::Mat_<double>(1, 5) << -0.092835, 0.505198, -0.007164, 0.006000, 0.000000);

    // 5. 输出旋转向量和位移向量
    cv::Mat rvec, tvec;

    // 6. 执行 PnP 求解
    bool success = cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);

    // 7. 打印结果
    if (success)
    {
        std::cout << "Rotation Vector (rvec):\n"
                  << rvec << std::endl;
        std::cout << "\nTranslation Vector (tvec):\n"
                  << tvec << std::endl;

        // 可选：将旋转向量转换为旋转矩阵
        cv::Mat R;
        cv::Rodrigues(rvec, R);
        std::cout << "\nRotation Matrix:\n"
                  << R << std::endl;
    }
    else
    {
        std::cerr << "solvePnP failed!" << std::endl;
    }

    return 0;
}
