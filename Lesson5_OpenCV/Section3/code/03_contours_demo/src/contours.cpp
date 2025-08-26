#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // 1. 处理命令行传参
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold>" << std::endl;
        return -1;
    }

    // 2. 读取图像
    cv::Mat bgr_image = cv::imread(argv[1]);
    if (bgr_image.empty()) {
        std::cerr << "无法加载图像！" << std::endl;
        return -1;
    }

    // 3. 从命令行获取阈值
    int binary_thres=std::stoi(argv[2]);


    // 4. 图像预处理（二值化）
    cv::Mat gray_image, binary_img;
    cv::cvtColor(bgr_image, gray_image, cv::COLOR_BGR2GRAY); // brg转gray
    cv::threshold(gray_image, binary_img, binary_thres, 255, cv::THRESH_BINARY); // 二值化

    // 5. 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary_img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // 6. 创建原图副本并在上面绘制轮廓
    cv::Mat image_with_contours = bgr_image.clone();  // 创建深拷贝
    cv::drawContours(image_with_contours, contours, -1, cv::Scalar(0, 255, 0), 2);  // 绘制所有轮廓

    cv::imshow("Original Image", bgr_image);
    cv::imshow("Binary Image", binary_img);
    cv::imshow("Contours on Original", image_with_contours);

    // 9. 保存结果
    cv::imwrite("original_with_contours.jpg", image_with_contours);

    cv::waitKey(0);
    return 0;
}