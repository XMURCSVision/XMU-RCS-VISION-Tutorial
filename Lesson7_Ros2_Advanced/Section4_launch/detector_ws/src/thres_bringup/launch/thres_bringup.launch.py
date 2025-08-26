# 导入必要的Python模块
import os
import sys
import yaml
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import Command

# 将当前包的launch目录添加到系统路径中，以便可以导入其他launch文件
sys.path.append(os.path.join(get_package_share_directory('thres_bringup'), 'launch'))

def generate_launch_description():
    """
    生成ROS2 launch描述的入口函数
    返回一个LaunchDescription对象，包含所有需要启动的节点和动作
    """
    
    # 导入ROS2 launch相关的类和函数
    from launch_ros.descriptions import ComposableNode
    from launch_ros.actions import ComposableNodeContainer, Node, SetParameter, PushRosNamespace
    from launch.actions import TimerAction, Shutdown
    from launch import LaunchDescription

    # 获取参数文件的路径
    # 假设参数文件位于thres_bringup包的config目录下，名为node_params.yaml
    node_params = os.path.join(
        get_package_share_directory('thres_bringup'), 
        'config', 
        'node_params.yaml'
    )

    # 创建图像处理节点
    # 使用ComposableNode可以更高效地利用进程内通信
    img_node = ComposableNode(
        package='thres_pkg',       # 节点所在的包名
        plugin='thres::ImgNode',  # 节点的插件名称(类名)
        name='image_node',          # 节点名称
        parameters=[node_params], # 传递给节点的参数文件
        extra_arguments=[{'use_intra_process_comms': True}],  # 启用进程内通信
    )


    # 延迟启动节点(5秒后启动)
    delay_thres_node = TimerAction(
        period=2.0,  # 延迟时间(秒)
        actions=[img_node],  # 要延迟执行的动作
    )

    # 返回LaunchDescription对象，包含所有要启动的组件
    return LaunchDescription([
        delay_thres_node,  
        # 组件
    ])
