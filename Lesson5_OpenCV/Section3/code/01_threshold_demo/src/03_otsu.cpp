#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold>" << std::endl;
        return -1;
    }

    std::string image_path = argv[1];
    cv::Mat src = cv::imread(image_path, cv::IMREAD_GRAYSCALE);

    // 2. 创建输出矩阵
    Mat dst;

    // 3. 应用Otsu阈值分割
    double otsuThresh = threshold(src, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // 4. 显示结果和计算出的阈值
    cout << "Otsu算法计算的最佳阈值: " << otsuThresh << endl;

    namedWindow("原始图像", WINDOW_AUTOSIZE);
    namedWindow("Otsu阈值分割结果", WINDOW_AUTOSIZE);

    imshow("原始图像", src);
    imshow("Otsu阈值分割结果", dst);

    // 5. 可选：绘制直方图（帮助理解Otsu原理）
    Mat hist;
    int histSize = 256;
    float range[] = {0, 256};
    const float *histRange = {range};
    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    // 归一化直方图
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // 绘制直方图
    for (int i = 1; i < histSize; i++)
    {
        line(histImage,
             Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
             Scalar(0, 0, 255), 2, 8, 0);
    }

    // 在直方图上标记Otsu阈值
    line(histImage,
         Point(bin_w * otsuThresh, 0),
         Point(bin_w * otsuThresh, hist_h),
         Scalar(0, 255, 0), 2, 8, 0);

    putText(histImage, "Otsu Threshold: " + to_string(otsuThresh),
            Point(50, 50), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 0), 2);

    namedWindow("灰度直方图", WINDOW_AUTOSIZE);
    imshow("灰度直方图", histImage);

    // 6. 保存结果
    imwrite("otsu_threshold_result.jpg", dst);

    // 7. 等待按键退出
    waitKey(0);
    return 0;
}