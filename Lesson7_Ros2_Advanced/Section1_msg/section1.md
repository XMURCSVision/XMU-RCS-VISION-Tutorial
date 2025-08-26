# Ros2中的消息

- [ros2官方文档](https://docs.ros.org/en/foxy/index.html)

## I.通信机制架构

## II.常见官方消息类型

| 消息类型                              | 常见字段                                                 | 应用场景         | 示例代码片段                                           |
| --------------------------------- | ---------------------------------------------------- | ------------ | ------------------------------------------------ |
| `std_msgs/String`                 | `data: string`                                       | 文本通信、调试      | `std_msgs::msg::String msg; msg.data = "Hello";` |  
| `geometry_msgs/Point`             | `x, y, z: float64`                                   | 坐标点          | `msg.x = 1.0; msg.y = 2.0;`  |
| `geometry_msgs/Pose`              | `position: Point`, `orientation: Quaternion`         | 位置 + 姿态      | `msg.position.x = 1.0;` |
| `geometry_msgs/Twist`             | `linear: Vector3`, `angular: Vector3`                | 速度指令，常用于小车   | `msg.linear.x = 0.5;`  |
| `sensor_msgs/Image`               | `height, width, encoding, data`                      | 图像传输         | 订阅摄像头数据        |
| `sensor_msgs/PointCloud2`         | `header, height, width, fields, data`                | 雷达/点云数据      | 处理 3D 点云   |
| `nav_msgs/Odometry`               | `pose, twist`                                        | 位姿 + 速度，导航常用 | 用于里程计发布   |
| `nav_msgs/Path`                   | `poses[]`                                            | 轨迹路径         | 控制器规划路径   |  
| `visualization_msgs/Marker`       | `type, pose, scale, color`                           | RViz 可视化物体   | 可画点线面  |   
                                     
### (1)图像类型消息 `sensor_msgs/Image`

> 实操要求：pkg create ，将ori的代码，改成节点  
>
> 节点名为`ImgNode`，回调函数将订阅到的rgb图像，转成灰度图(`cv::cvtColor`)，并使用窗口展示  
>
> 发布使用timer_，每3s发布一次；订阅回调函数，窗口`waitKey`设置为2.5s  

> 提示如下：（其余翻5月文档或ai）
```C++
// 提示1：发布者订阅者的消息类型
sensor_msgs::msg::Image img_pub_; // 图像的ros2消息发布者
sensor_msgs::msg::Image img_sub_; // 图像ros2消息订阅者
```
```C++
// 提示2：timer定时器

// hpp声明
rclcpp::TimerBase::SharedPtr timer_;

// cpp实现(在节点构造函数中)
timer_ = this->create_wall_timer(std::chrono::seconds(5), std::bind(&ImgNode::ImgPublish, this));
```
```C++
// 提示3：bind写法示例
std::bind(&ImgNode::ImgCallback, this, std::placeholders::_1) // bind绑定函数
```
```C++
// main函数与ros2 run
#include "img_demo/img_node.hpp"

int main(int argc, char *argv[])
{

    rclcpp::init(argc, argv);

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <image_path> <binary_threshold>" << std::endl;
        return 1;
    }

    auto node = std::make_shared<ImgNode>("image_node", argv[1], std::stoi(argv[2]));

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
```
```C++
// 如果要spin多个节点
int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    
    // 创建节点实例
    auto node1 = std::make_shared<Node1>();
    auto node2 = std::make_shared<Node2>();
    
    // 单线程执行器（自动处理所有节点的回调）
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node1);
    executor.add_node(node2);
    
    // 阻塞直到收到退出信号（Ctrl+C）
    executor.spin();
    
    rclcpp::shutdown();
    return 0;
}
```
```bash
# 提示4：pkg创建指令
ros2 pkg create 01_img_demo --build-type ament_cmake --dependencies sensor_msgs opencv rclcpp cv_bridge --license Apache-2.0

# 提示5：ros2 run
ros2 run img_demo main ../path.jpg 160
```


## III.自定义消息类型
```msg
# Armor.msg
std_msgs/Header header
string frame_id
string armor_id
geometry_msgs/msg/PoseStamped posestamped
```

自定义消息类型，写好依赖之后，放入ws一起编译

3份代码：  
img_demo 为imshow的ros2版  
auto_aim_interfaces 为自定义消息  
image_ws 为完整的pkg示例  
