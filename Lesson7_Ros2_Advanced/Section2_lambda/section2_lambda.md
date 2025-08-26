# lambda表达式+订阅回调函数

- [lambda讲解参考](https://www.bilibili.com/video/BV13MmUYUE9S?vd_source=7f8884af7fd7d142a4a56a0e52735937)

## cpp:lambda表达式
作用：快速定义一个匿名函数对象  
```C++
[捕获变量](参数列表) 可选限定符->返回类型 {
    // 函数内容
}
```
例如：
```C++

int main()
{
    int x=1;
    int y=2;
    auto p=[x,y](int a,int b)->int{
        return a+b;
    }

    std::cout<<p(4,6);
}
```


## 使用lambda表达式写回调函数

bind绑定
```C++
img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image/show",           // 订阅话题名
        rclcpp::SensorDataQoS(), // QoS 设置（也可以用 rclcpp::QoS(10)）
        std::bind(&ImgNode::ImgCallback, this, std::placeholders::_1) // bind绑定函数
        );
```

lambda表达式
```C++
img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
    "/image/show",            // 订阅话题名
    rclcpp::SensorDataQos(),  // QoS 设置（也可以用 rclcpp::QoS(10)）
    [this](const sensor_msgs::msg::Image::SharedPtr msg){ // lambda表达式
        // function
    }
    );
```

任务：修改image_ws中的回调  
(把image_ws复制到此文件夹下，再修改)(复制前记得把编译文件删了)