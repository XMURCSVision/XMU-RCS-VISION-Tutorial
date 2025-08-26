#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat img;
    img = cv::imread("../sentry.jpg", cv::IMREAD_COLOR);
    cv::namedWindow("Sentry", cv::WINDOW_NORMAL);
    cv::imshow("Sentry", img);

    while (true)
    {
        if (cv::waitKey(0) == 27)
            break;
    }

    cv::destroyAllWindows();
    return 0;
}