# Parameter
参数和yaml

- [ros2 document](https://docs.ros.org/en/humble/Concepts/Basic/About-Parameters.html)
- [Using parameter in a class C++](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Using-Parameters-In-A-Class-CPP.html)

## 0.初识yaml

## I.ros2中的参数机制

### 1.`declare_parameter`
- `declare_parameter` 是 `Node` 类的成员函数，用于声明节点参数，返回值是
- 返回值为 `rclcpp::ParameterValue`（参数的包装值类型）
- 一般对`declare_parameter`函数进行重载

#### (1) 声明参数（带默认值）

```C++
// (1) 声明参数（带默认值）
template<typename T>
rclcpp::ParameterValue declare_parameter(
    const std::string &name,  // 参数名
    const T &default_value,   // 默认值
    const rcl_interfaces::msg::ParameterDescriptor &parameter_descriptor = rcl_interfaces::msg::ParameterDescriptor(), // 参数描述，可设定范围
    bool ignore_override = false
);

// 示例：设置整数范围约束
    thresh_desc.integer_range.resize(1);
    thresh_desc.integer_range[0].from_value = 0;   // 最小值
    thresh_desc.integer_range[0].to_value = 255;   // 最大值
    thresh_desc.integer_range[0].step = 1;         // 步长

    // 2. 声明带范围约束的参数
    this->declare_parameter("binary_thresh", 60, thresh_desc);
```

#### (2)声明无默认值的参数

```C++
// (2) 声明无默认值的参数（需通过 YAML 或命令行传入）
rclcpp::ParameterValue declare_parameter(
    const std::string &name,
    const rcl_interfaces::msg::ParameterDescriptor &parameter_descriptor = rcl_interfaces::msg::ParameterDescriptor(),
    bool ignore_override = false
);
```
```C++
// 示例
// 声明参数
    this->binary_thres = declare_parameter("thresh", 60);
```

### 2.`get_parameter`
把参数名对应的参数值，赋给某个变量

### 3.`add_on_parameter_set_callback()`
```C++
// 添加参数回调
    param_callback_handle_ = this->add_on_set_parameters_callback(
        std::bind(&ImgNode::parametersCallback, this, std::placeholders::_1));

```

### 4.参数与rqt动态调参
```C++
// 声明参数并设置范围描述符
    rcl_interfaces::msg::ParameterDescriptor thresh_desc; // descriptor
    thresh_desc.description = "binary_thres(0-255)";
    thresh_desc.integer_range.resize(1); // 分配一个 IntegerRange 元素
    thresh_desc.integer_range[0].from_value = 0;
    thresh_desc.integer_range[0].to_value = 255;
    thresh_desc.integer_range[0].step = 1;
```


## II.yaml与launch结合，单独封装
- [示例：自瞄yaml](https://github.com/Lori-Lai/XMU-RCS-RM-VISION/blob/main/src/rm_vision_bringup/config/node_params.yaml)

