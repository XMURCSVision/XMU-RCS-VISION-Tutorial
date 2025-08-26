#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main()
{
    // 1. 打开一个mp4
    cv::VideoCapture cap("../videos/RM.mp4");
    if (!cap.isOpened())
    {
        std::cerr << "failed to open the video" << std::endl;
        return -1;
    }

    // 2. 获取视频属性
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);
    if (fps == 0)
        fps = 30.0;
    int delay = static_cast<int>(1000.0 / fps); // 计算每帧显示时间（ms）
    cv::Size frame_size(frame_width, frame_height);

    // 3. 读取所有帧
    std::vector<cv::Mat> frames;
    cv::Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;
        frames.push_back(frame.clone());
    }
    cap.release();

    std::cout << "总帧数: " << frames.size() << std::endl;

    // 4. 打开 VideoWriter 保存为 mp4 文件
    cv::VideoWriter writer;
    bool isOpened = writer.open(
        "../videos/output_reverse.mp4",
        cv::VideoWriter::fourcc('m', 'p', '4', 'v'), // 注意编码器
        fps,
        frame_size);

    if (!isOpened)
    {
        std::cerr << "无法打开输出视频文件 writer！" << std::endl;
        return -1;
    }

    // 5. 倒序写入帧
    for (int i = static_cast<int>(frames.size()) - 1; i >= 0; --i)
    {
        writer.write(frames[i]);
        cv::imshow("Writing Reverse", frames[i]);
        if (cv::waitKey(delay) == 27)
            break; // ESC 也可以中止写入
    }

    writer.release();
    cv::destroyAllWindows();

    return 0;
}
