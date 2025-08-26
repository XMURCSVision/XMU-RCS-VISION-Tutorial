#ifndef SOLVER_NODE_HPP // if not define
#define SOLVER_NODE_HPP // define

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>

using namespace std;

namespace solver
{
    class SolverNode : public rclcpp::Node
    {
    public:
        explicit SolverNode(const rclcpp::NodeOptions &options);
        ~SolverNode();

        void topic_callback(const std_msgs::msg::String::SharedPtr msg);

    private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr solver_subscription_;
        // solver_sub_;
    };
}

#endif // SOLVER_NODE_HPP