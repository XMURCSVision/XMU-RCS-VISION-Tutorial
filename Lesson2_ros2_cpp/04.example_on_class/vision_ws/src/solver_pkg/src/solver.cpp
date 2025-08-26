#include "solver_pkg/solver.hpp"

namespace solver
{

    SolverNode::SolverNode(const rclcpp::NodeOptions &options) : rclcpp::Node("solver_node", options)
    {
        solver_subscirption_ = this->create_subscription<std_msgs::msg::String>(
            "/armor_detector", 10,
            std::bind(&SolverNode::topic_callback, this, std::placeholders::_1));
    }
    SolverNode::~SolverNode()
    }

    void SolverNode::topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "sub:%s", msg->data.c_str());
    }
}

#include "rclcpp_components/register_node_macro.hpp" //这行宏放在cpp最后
RCLCPP_COMPONENTS_REGISTER_NODE(solver::SolverNode)