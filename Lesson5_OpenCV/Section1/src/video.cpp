#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 1. 打开一个mp4
    cv::VideoCapture cap("../videos/RM.mp4");
    if (!cap.isOpened())
    {
        std::cerr << "failed to open the video" << std::endl;
        return -1;
    }

    double fps = cap.get(cv::CAP_PROP_FPS); // 获取帧率
    if (fps == 0)
        fps = 30.0;
    int delay = static_cast<int>(1000.0 / fps); // 计算每帧显示时间（ms）（给waitKey使用）

    // 2.按帧循环imshow
    cv::Mat frame; // frame 为一帧
    while (true)
    {
        cap >> frame; // 从视频中读取一帧

        if (frame.empty())
            break;

        cv::imshow("Video Playback", frame); // 显示
        // 按下 ESC 键退出
        if (cv::waitKey(delay) == 27) // 每帧停留25ms，如果按下Esc，则终止循环
            break;
    }

    // 3.释放资源
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
