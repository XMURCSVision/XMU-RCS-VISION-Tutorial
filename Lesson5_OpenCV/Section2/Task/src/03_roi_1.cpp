// task_1.cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 1. 读取图像
    cv::Mat image = cv::imread("../../images/task_3.jpg");
    if (image.empty())
    {
        std::cerr << "error task_3.jpg" << std::endl;
        return -1;
    }

    // 2. 创建一个与原图大小相同、类型一致的黑色背景图
    // cv::Mat::zeros 会创建一个所有像素都为0的图像
    cv::Mat blackBackground = cv::Mat::zeros(image.size(), image.type());

    // 3. 定义一个感兴趣区域 (ROI)
    // 您可以修改这里的 x, y, width, height 来选择不同的区域
    // 注意：要确保 ROI 在图像边界之内
    int roi_x = image.cols / 4;      // 从宽度的 1/4 处开始
    int roi_y = image.rows / 4;      // 从高度的 1/4 处开始
    int roi_width = image.cols / 2;  // ROI 宽度为原图的一半
    int roi_height = image.rows / 2; // ROI 高度为原图的一半
    cv::Rect roi(roi_x, roi_y, roi_width, roi_height);

    // 4. 从原图中提取 ROI
    // 这里我们直接获取原图 ROI 的 "视图"，没有复制数据
    cv::Mat imageROI = image(roi);

    // 5. 将提取出的 ROI 复制到黑色背景图的相应位置
    // 首先，在黑色背景上获取一个目标区域的 "视图"
    cv::Mat destROI = blackBackground(roi);
    // 然后，使用 copyTo 将 imageROI 的内容复制到 destROI
    imageROI.copyTo(destROI);

    // 6. 显示原图和结果图
    cv::imshow("Image_Raw", image);
    cv::imshow("ROI", blackBackground);

    // 7. 保存结果
    cv::imwrite("../output/task_3_result.jpg", blackBackground);
    std::cout << "safed as  task_3_result.jpg " << std::endl;

    // 8. 等待按键后退出
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}