// Copyright 2022 Chen Jun

//这是？数字识别？
//没有完全注释

#ifndef ARMOR_DETECTOR__NUMBER_CLASSIFIER_HPP_
#define ARMOR_DETECTOR__NUMBER_CLASSIFIER_HPP_

// OpenCV
#include <opencv2/opencv.hpp>

// STL
#include <cstddef>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "armor_detector/armor.hpp"

namespace rm_auto_aim
{
class NumberClassifier  
{
public:
  NumberClassifier(  
    const std::string & model_path, const std::string & label_path, const double threshold,
    const std::vector<std::string> & ignore_classes = {});
    //？？神经网络数字识别

  void extractNumbers(const cv::Mat & src, std::vector<Armor> & armors);

  void classify(std::vector<Armor> & armors);  

  double threshold;  //阈值处理

private:
  cv::dnn::Net net_;   //OpenCV库中神经网络的一个类
  std::vector<std::string> class_names_;
  std::vector<std::string> ignore_classes_;
};
}  // namespace rm_auto_aim

#endif  // ARMOR_DETECTOR__NUMBER_CLASSIFIER_HPP_
