// task_1_revised.cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 1. 读取图像
    cv::Mat image = cv::imread("../images/task_3.jpg");
    if (image.empty())
    {
        std::cerr << "错误: 无法加载图像 ../images/task_3.jpg" << std::endl;
        return -1;
    }

    // 2. 创建一个原图的副本，我们将在这个副本上进行操作
    // 使用 .clone() 进行深拷贝，这样后续操作不会影响原始图像
    cv::Mat result = image.clone();

    // 3. 定义你感兴趣的区域 (ROI)
    // 您可以修改这里的 x, y, width, height 来选择不同的区域
    int roi_x = image.cols / 4;
    int roi_y = image.rows / 4;
    int roi_width = image.cols / 2;
    int roi_height = image.rows / 2;
    cv::Rect roi(roi_x, roi_y, roi_width, roi_height);

    // --- 核心逻辑: 将ROI之外的区域置为黑色 ---
    // 我们可以将 "ROI之外的区域" 看作是四个独立的矩形：
    // 一个在ROI上方，一个在ROI下方，一个在ROI左侧，一个在ROI右侧。
    // 我们将依次把这四个区域的像素设置为0。

    // 4. 将ROI上方的区域变黑
    // 区域从 (0, 0) 开始，宽度为整个图像，高度到ROI的y坐标
    cv::Rect top_rect(0, 0, result.cols, roi.y);
    result(top_rect).setTo(cv::Scalar(0, 0, 0));

    // 5. 将ROI下方的区域变黑
    // 区域从 (0, roi.y + roi.height) 开始，宽度为整个图像，高度为剩余部分
    cv::Rect bottom_rect(0, roi.y + roi.height, result.cols, result.rows - (roi.y + roi.height));
    result(bottom_rect).setTo(cv::Scalar(0, 0, 0));

    // 6. 将ROI左侧的区域变黑
    // 区域从 (0, roi.y) 开始，宽度到ROI的x坐标，高度为ROI的高度
    cv::Rect left_rect(0, roi.y, roi.x, roi.height);
    result(left_rect).setTo(cv::Scalar(0, 0, 0));

    // 7. 将ROI右侧的区域变黑
    // 区域从 (roi.x + roi.width, roi.y) 开始，宽度为剩余部分，高度为ROI的高度
    cv::Rect right_rect(roi.x + roi.width, roi.y, result.cols - (roi.x + roi.width), roi.height);
    result(right_rect).setTo(cv::Scalar(0, 0, 0));

    // 8. 显示原图和结果图
    cv::imshow("Raw", image);
    cv::imshow("Task3", result);

    // 9. 保存结果
    cv::imwrite("../output/task_3_result_revised.jpg", result);
    std::cout << "saved as task_1_result_revised.jpg" << std::endl;

    // 10. 等待按键后退出
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}