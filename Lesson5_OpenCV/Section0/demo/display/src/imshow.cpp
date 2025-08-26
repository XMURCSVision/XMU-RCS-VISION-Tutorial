#include <stdio.h>

#include <opencv2/opencv.hpp>

using namespace cv;

int main() // 在命令行传参指定图像
{

    Mat image1;

    // 读取图像
    image1 = imread("../RM.jpg", IMREAD_COLOR);

    // 创建一个名为 "Display Image" 的窗口，方式为 WINDOW_AUTOSIZE
    namedWindow("Display Image", WINDOW_AUTOSIZE);

    // 用 "Display Image" 窗口显示图像 image1
    imshow("Display Image", image1);

    // 让窗口停留5000ms
    waitKey(5000); // ms
    waitKey(0);

    destroyAllWindows();

    return 0;
}