#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>

using namespace std;

namespace solver
{
    class SolverNode : public rclcpp::Node
    {
    public:
        SolverNode(const rclcpp::NodeOptions &options);
        ~SolverNode();

        // 回调函数
        void topic_callback(const std_msgs::msg::String::SharedPtr msg);

    private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr solver_subscirption_;
    };
}

#endif