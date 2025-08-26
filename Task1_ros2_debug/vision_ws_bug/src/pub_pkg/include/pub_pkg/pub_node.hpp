#ifndef PUB_NODE_HPP
#define PUB_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <string>
using namespace std;

namespace pub
{
    class PubNode : public rclcpp::Node
    {
    public:
        explicit PubNode(const rclcpp::NodeOptions &options); // 因为注册成了components，所以搭配使用NodeOptions // explicit防止隐式调用
        ~PubNode();

        void toPublish();

    private:
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_; // 一个定时器，让消息按计时持续发送
    };

} // pub

#endif // PUB_NODE_HPP