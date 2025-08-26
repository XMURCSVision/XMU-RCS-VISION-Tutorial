#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 读取彩色图
    cv::Mat src = cv::imread("../../images/deepsleep.jpg", cv::IMREAD_COLOR);
    if (src.empty())
    {
        std::cerr << "图像读取失败！" << std::endl;
        return -1;
    }

    // 参数：上、下、左、右边框宽度
    int top = 50;
    int bottom = 50;
    int left = 100;
    int right = 100;

    // 输出图像
    cv::Mat dst;

    // 添加蓝色边框（常量填充值），边框类型为BORDER_CONSTANT
    cv::copyMakeBorder(src, dst, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(255, 0, 0));

    // 显示
    cv::imshow("Original Image", src);
    cv::imshow("Image with Blue Border", dst);

    cv::imwrite("../images/ds_border.jpg", dst);

    std::cout << "按 ESC 键关闭所有窗口\n";
    while (true)
    {
        int key = cv::waitKey(0);
        if (key == 27) // ESC键
            break;
    }
    cv::destroyAllWindows();

    return 0;
}
