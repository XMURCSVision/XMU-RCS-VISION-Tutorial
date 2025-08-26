#include <stdio.h>

#include <opencv2/opencv.hpp>

int main()
{
  cv::Mat image;
  image = cv::imread("../images/deepsleep.jpg", cv::IMREAD_GRAYSCALE); // 读取图像

  cv::namedWindow("Display Image", cv::WINDOW_NORMAL); // 创建窗口
  cv::imshow("Display Image", image);                  // 显示图像

  int keyboard = cv::waitKey(0);
  if (keyboard == 27) // 如果按ESC，那么销毁窗口
  {
    std::cout << "quit" << std::endl;
    cv::imwrite("../images/output1.jpg", image);
    cv::destroyAllWindows();
  }
  else
  {
    cv::destroyAllWindows();
  }

  return 0;
}