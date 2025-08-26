#include <opencv2/opencv.hpp>

using namespace cv;

int r = 0, g = 0, b = 0;

void on_trackbar(int, void *)
{
    // 创建一个纯色图像（300x500）
    Mat color(300, 500, CV_8UC3, Scalar(b, g, r));
    imshow("RGB Mixer", color);
}

int main()
{
    // 创建窗口
    namedWindow("RGB Mixer", WINDOW_AUTOSIZE);

    // 创建滑动条
    createTrackbar("R", "RGB Mixer", &r, 255, on_trackbar);
    createTrackbar("G", "RGB Mixer", &g, 255, on_trackbar);
    createTrackbar("B", "RGB Mixer", &b, 255, on_trackbar);

    // 初始显示一次
    on_trackbar(0, 0);

    // 等待退出（按 ESC 键）
    while (true)
    {
        int key = waitKey(10);
        if (key == 27)
            break; // ESC
    }

    destroyAllWindows();
    return 0;
}
