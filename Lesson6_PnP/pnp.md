# PnP --Perspective-n-Point

学习目标：会使用cv::solvePnP，无需掌握数学原理

## 0.数学原理
此部分不在课上讲解，感兴趣的同学可自行了解。   
PnP主要算法原理有如下几种：  
- [SVD奇异值分解](【点云配准教程第四讲：点云配准的基本数学模型及其SVD求解方法】https://www.bilibili.com/video/BV1AN41177dG?vd_source=7f8884af7fd7d142a4a56a0e52735937)
- [EPnP](https://www.bilibili.com/video/BV1a441177me?vd_source=7f8884af7fd7d142a4a56a0e52735937)
- [P3P](https://www.bilibili.com/video/BV1g9CdY4EeL?vd_source=7f8884af7fd7d142a4a56a0e52735937)

- [完整讲解](https://www.bilibili.com/video/BV1a441177me?vd_source=7f8884af7fd7d142a4a56a0e52735937)

- [csdn笔记](https://blog.csdn.net/qq_19319481/article/details/134013308)

参考书籍：《视觉SLAM十四讲》7.7-7.8

---

## I. PnP介绍及作用
1. PnP是什么？

* PnP = Perspective-n-Point（透视n点问题）
* 目标：根据已知的 **n个三维点（3D）** 和它们在图像中的 **二维投影点（2D）**，计算相机与物体之间的空间关系  
* 具体来说，求出两个坐标系之间的旋转（R）和平移（t）


2. 为什么要做PnP？

* 实际应用中，相机拍摄到的是二维图像，但机器人或系统需要知道目标的 **三维空间位置和姿态**  
* PnP将图像2D转回世界坐标系3D，Pc与Pw之间的坐标变换关系  

3. PnP的输入是什么？

* 物体上的已知 **3D点**（例如装甲板四个角的实际坐标）
* 这些3D点在图像上的对应 **2D像素点**
* 相机的内参（相机焦距、光心等参数）

4. PnP的输出是什么？

* 旋转矩阵 R：描述相机坐标系如何旋转到物体坐标系
* 平移向量 t：描述相机坐标系到物体坐标系的平移量
* 这两个一起定义了相机相对于物体的 **6自由度空间位姿**

---

## II.库

| 库 / 方法             | 支持算法                               | 特点                            | 编程语言         |
| ------------------ | ---------------------------------- | ----------------------------- | ------------ |
| **OpenCV**         | P3P、EPnP、ITERATIVE、AP3P、RANSAC-PnP | 工程常用、接口简单                     | C++ / Python |
| **ceres-solver**   | 自定义优化（非线性）                         | 精度高，可配约束，适合 Bundle Adjustment | C++          |
| **g2o**            | 优化框架，支持位姿图+PnP                     | 常用于 SLAM 中的 BA、PnP 后端优化       | C++          |
| **colmap**         | 使用 PnP 进行图像配准                      | 内部调用 P3P、EPnP、LHM 等           | C++          |
| **OpenGV**         | 支持多种 PnP（P3P, GP3P, EPnP, etc）     | 几何视觉专用，支持多相机模型                | C++          |
| **ViSP**           | EPnP、Dementhon、LHM、UPnP            | 适合视觉伺服和工业机器人                  | C++          |
| **Eigen + 手写最小二乘** | 自己构建误差项 + 高斯牛顿/SVD                 | 教学和实验用，灵活性高                   | C++          |


### 1.cv::solvePnP
```C++
bool cv::solvePnP(
    InputArray objectPoints,         // 3D 点坐标（世界坐标系）
    InputArray imagePoints,          // 2D 像素坐标（图像坐标系）
    InputArray cameraMatrix,         // 相机内参矩阵
    InputArray distCoeffs,           // 畸变参数
    OutputArray rvec,                // 输出旋转向量（Rodrigues 形式）
    OutputArray tvec,                // 输出平移向量
    bool useExtrinsicGuess = false,  // 是否提供初值（rvec/tvec）
    int flags = cv::SOLVEPNP_ITERATIVE // 使用的PnP算法
);
```

| 参数名                 | 类型                | 含义与说明                                                         |
| ------------------- | ----------------- | ------------------------------------------------------------- |
| `objectPoints`      | `cv::InputArray`  | 3D 世界坐标点，常为 `std::vector<cv::Point3f>`，大小为 Nx3                |
| `imagePoints`       | `cv::InputArray`  | 对应的 2D 图像像素点，常为 `std::vector<cv::Point2f>`，大小为 Nx2            |
| `cameraMatrix`      | `cv::InputArray`  | 相机内参矩阵 $3 \times 3$，包含 fx, fy, cx, cy 等                       |
| `distCoeffs`        | `cv::InputArray`  | 畸变系数（可为空），`cv::Mat` 或 `std::vector<float>`，长度可为 4、5、8、12 或 14 |
| `rvec`              | `cv::OutputArray` | 输出的旋转向量（Rodrigues 格式，3×1），可转为旋转矩阵                             |
| `tvec`              | `cv::OutputArray` | 输出的平移向量（3×1），表示相机在目标坐标系下的位置                                   |
| `useExtrinsicGuess` | `bool`            | 是否提供初始 `rvec`/`tvec` 值以优化求解（默认 false）                         |
| `flags`             | `int`             | 使用的算法类型，见下方算法列表（如 `cv::SOLVEPNP_ITERATIVE`）                   |



示例：
```cpp
std::vector<cv::Point3f> objectPoints = {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}}; // 3D
std::vector<cv::Point2f> imagePoints = {{523, 441}, {600, 440}, {601, 500}, {524, 501}}; // 2D
cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) << 
  800, 0, 320,
  0, 800, 240,
  0, 0, 1
); // 相机内参矩阵
cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F); // 相机畸变系数

cv::Mat rvec, tvec; // 输出的rvec和tvec

cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec); // 调用cv::solvePnP
```


