#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    // 1.处理命令行参数
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold>" << std::endl;
        return -1;
    }

    // 读取图像
    cv::Mat src = cv::imread(argv[1]);
    if (src.empty())
    {
        std::cerr << "Error: Could not load image!" << std::endl;
        return -1;
    }

    // 转换 ksize（确保是正奇数）
    int ksize = std::stoi(argv[2]);
    if (ksize <= 0 || ksize % 2 == 0)
    {
        std::cerr << "Error: ksize must be a positive odd number!" << std::endl;
        return -1;
    }

    // 2. 创建输出图像
    cv::Mat dst;

    // 3. 应用均值模糊（内核大小 5x5）
    cv::blur(src, dst, cv::Size(ksize, ksize)); // 内核越大，模糊效果越强

    // 4. 显示结果
    cv::imshow("Original Image", src);
    cv::imshow("Blurred Image (Mean Blur)", dst);

    // 5. 保存结果（可选）
    cv::imwrite("../output/blurred_output.jpg", dst);

    // 6. 等待按键退出
    cv::waitKey(0);
    return 0;
}