from launch import LaunchDescription 
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode # 组合节点的配置

def generate_launch_description():
    container = ComposableNodeContainer( # 实例化、构造函数
        name='vision_container', # 自定义一个名字
        namespace='',
        package='rclcpp_components',
        executable='component_container_mt',
        composable_node_descriptions=[              
            ComposableNode(
                package='pub_pkg',             # pkg名
                plugin='pub::PubNode',    # namespace::ClassName
                name='pub_node'                # NodeName
            ),
            ComposableNode(
                package='sub_pkg',
                plugin='sub::SubNode',
                name='sub_node'
            )
        ],
        output='screen'
    )

    return LaunchDescription([container])
