#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 定义视频文件的名称和编码格式
    std::string filename = "../videos/output_circle.mp4";
    int codec = cv::VideoWriter::fourcc('M', 'P', '4', 'V'); // mp4编码
    double fps = 30.0;                                       // 每秒30帧

    // 创建 VideoWriter 对象
    cv::VideoWriter writer;
    writer.open(filename, codec, fps, cv::Size(640, 480), true);

    // 检查 VideoWriter 是否成功打开
    if (!writer.isOpened())
    {
        std::cerr << "无法打开视频文件进行写入" << std::endl;
        return -1;
    }

    // 创建一个用于写入的视频帧
    cv::Mat frame = cv::Mat::zeros(480, 640, CV_8UC3); // 全0,8位无符号BGR三通道

    // 主循环：生成一些简单的动画
    for (int i = 0; i < 100; ++i)
    {
        // 填充帧数据 (例如，绘制一个移动的圆)
        frame.setTo(cv::Scalar(0, 0, 0)); // 清空帧
        cv::circle(frame, cv::Point(320, 240), i, cv::Scalar(255, 0, 0), -1);

        cv::imshow("Frame", frame);
        if (cv::waitKey(30) >= 0)
            break; // 按任意键退出

        // 将帧写入视频文件
        writer.write(frame);
    }

    writer.release();
    cv::destroyAllWindows();
}