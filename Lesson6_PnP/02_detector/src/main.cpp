#include "detector/detector.hpp"
#include "pnp_solver.hpp"
#include "armor.hpp"

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold> <detect_color (0:Red, 1:Blue)>" << std::endl;
        return -1;
    }

    std::string image_path = argv[1];
    int binary_thres = std::stoi(argv[2]);
    int detect_color = std::stoi(argv[3]);

    cv::Mat bgr_img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (bgr_img.empty())
    {
        std::cerr << "ERROR: Could not read image from: " << image_path << std::endl;
        return -1;
    }
    std::cout << "1. Image loaded successfully." << std::endl;

    Detector detector;
    PnpSolver pnp_solver;
    std::cout << "2. Detector and PnpSolver objects initialized." << std::endl;

    if (!detector.checkColor(bgr_img, detect_color))
    {
        std::cout << "Invalid" << std::endl;
        return 0;
    }
    std::cout << "3. Image color meets requirement, proceeding with processing." << std::endl;

    cv::Mat binary_img = detector.preprocessImage(bgr_img, binary_thres);
    std::cout << "4. Image preprocessed (grayscale and binary)." << std::endl;

    std::vector<std::vector<cv::Point>> light_bar_contours = detector.findContoursInBinary(binary_img);
    std::cout << "5. Number of contours found: " << light_bar_contours.size() << std::endl;

    cv::Mat display_img = bgr_img.clone();
    detector.drawContours(display_img, light_bar_contours);
    std::cout << "6. All raw contours drawn." << std::endl;

    // ====== 7. 直接写死相机参数 ======
    cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << 2334.43093, 0.0, 790.07101,
                             0.0, 2341.75513, 518.56545,
                             0.0, 0.0, 1.0);
    cv::Mat dist_coeffs = (cv::Mat_<double>(1, 5) << -0.092835, 0.505198, -0.007164, 0.006000, 0.000000);

    pnp_solver.setCameraParams(camera_matrix, dist_coeffs);
    std::cout << "7. Camera parameters manually set in main()." << std::endl;

    Armor_params armor_params(0.135, 0.055, 0.02, 0.055, 0.1);
    std::cout << "8. Armor physical parameters initialized." << std::endl;

    std::vector<cv::Point2f> image_points = pnp_solver.obtain2DCorners(light_bar_contours);
    bool corners_obtained = !image_points.empty();
    std::cout << "9. 2D armor corners obtained: " << (corners_obtained ? "Yes" : "No") << std::endl;

    std::vector<cv::Point3f> object_points = pnp_solver.obtain3DCorners(armor_params);
    std::cout << "10. 3D armor object points obtained: " << (object_points.size() == 4 ? "Yes" : "No") << std::endl;

    cv::Mat rvec, tvec;
    bool pnp_solved = false;
    if (corners_obtained && object_points.size() == 4)
    {
        pnp_solved = pnp_solver.solvePnP(object_points, image_points, rvec, tvec);
        std::cout << "11. PnP solution attempt completed. Success: " << (pnp_solved ? "Yes" : "No") << std::endl;
    }
    else
    {
        std::cout << "11. Skipping PnP solution due to insufficient 2D/3D points." << std::endl;
    }

    if (pnp_solved)
    {
        std::cout << "   Rotation Vector (rvec): " << rvec.t() << std::endl;
        std::cout << "   Translation Vector (tvec): " << tvec.t() << std::endl;
        double distance = cv::norm(tvec);
        std::cout << "   Distance to armor: " << distance << " meters" << std::endl;

        for (const auto &p : image_points)
            cv::circle(display_img, p, 5, cv::Scalar(0, 255, 255), -1);

        for (int i = 0; i < 4; ++i)
            cv::line(display_img, image_points[i], image_points[(i + 1) % 4], cv::Scalar(0, 255, 255), 2);
    }

    std::cout << "13. Displaying results." << std::endl;
    cv::imshow("Detected Contours & Armor PnP", display_img);
    cv::waitKey(0);

    return 0;
}
