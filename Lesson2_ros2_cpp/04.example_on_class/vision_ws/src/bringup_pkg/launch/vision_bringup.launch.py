from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    container = ComposableNodeContainer(
        name='vision_container', # 自定义一个名字
        namespace='',
        package='rclcpp_components',
        executable='component_container_mt',
        composable_node_descriptions=[              
            ComposableNode(
                package='detector_pkg',             # pkg名
                plugin='detector::DetectorNode',    # namespace::ClassName
                name='detector_node'                # NodeName
            ),
            ComposableNode(
                package='solver_pkg',
                plugin='solver::SolverNode',
                name='solver_node'
            )
        ],
        output='screen'
    )

    return LaunchDescription([container])
