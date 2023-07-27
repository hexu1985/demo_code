


### `1.2 编写ROS节点` 中 记录下来的一些命令

```
$ mkdir -p workspace/src
# cd workspace/src
$ catkin_create_pkg my_minimal_nodes roscpp std_msgs
# add cpp to my_minimal_nodes/src
# update CMakeLists.txt
# cd workspace dir
$ catkin_make
$ source devel/setup.bash
# tty1
$ roscore
# tty2
$ rosrun my_minimal_nodes my_minimal_publisher
# tty3
$ rosrun my_minimal_nodes my_minimal_subscriber
```

### `1.3.1 用catkin_simple简化CmakeLists.txt` 中 记录下来的一些命令

```
# clone catkin_make.git
# git clone git@github.com:catkin/catkin_simple.git
# cd workspace/src
# ln catkin_simple to catkin_simple.git dir

# cp cs_create_pkg.py
# alias cs_create_pkg='path of cs_create_pkg.py'
# example: alias cs_create_pkg='~/git/demo_code/ros/cs_create_pkg.py'

# cd workspace/src
$ cs_create_pkg my_minimal_nodes2 roscpp std_msgs

# start ros exe by launch file
# cd workspace dir
$ source devel/setup.bash
$ roslaunch my_minimal_nodes my_minimal_nodes.launch
```

### `2.1.1 定义一条自定义消息` 中 记录下来的一些命令

```
# 依赖于1.3.1的操作
# cd workspace/src
$ cs_create_pkg example_ros_msg roscpp std_msgs
# add ExampleMessage.msg
# cd workspace dir
$ catkin_make
# add cpp file and update CMakeLists.txt
$ catkin_make
# tty1
$ roscore
# tty2
$ source devel/setup.bash
$ rosrun example_ros_msg example_ros_message_publisher
# tty3
$ rostopic list
$ rostopic echo example_topic
```

### `2.2 服务介绍` 中 记录下来的一些命令

```
# cd workspace/src
$ cs_create_pkg example_ros_service roscpp std_msgs std_srvs
# add ExampleServiceMsg.srv
# cd workspace dir
$ catkin_make
# add cpp file and update CMakeLists.txt
$ catkin_make
# tty1
$ roscore
# tty2
$ source devel/setup.bash
$ rosrun example_ros_service example_ros_service
# tty3
$ rosservice list
$ rosservice call lookup_by_name 'Ted'
# tty4
$ source devel/setup.bash
$ rosrun example_ros_service example_ros_client
```

### `2.3 在ROS中使用C++类` 中 记录下来的一些命令

```
# cd workspace/src
$ cs_create_pkg example_ros_class roscpp std_msgs std_srvs
# cd workspace dir
# add cpp file and update CMakeLists.txt
$ catkin_make
# tty1
$ roscore
# tty2
$ rosrun example_ros_class example_ros_class
# tty3
$ rosservice call example_minimal_service
# tty4
$ rostopic pub -r 2 example_class_input_topic std_msgs/Float32 2.0
```

### `2.4 在ROS中创建库模块` 中 记录下来的一些命令

```
# cd workspace/src
$ cs_create_pkg creating_a_ros_library roscpp std_msgs std_srvs
# cd workspace dir
# add cpp file and update CMakeLists.txt
$ catkin_make
# tty1
$ roscore
# tty2
$ rosrun creating_a_ros_library ros_library_test_main
# tty3
$ rosservice call example_minimal_service
# tty4
$ rostopic pub -r 2 example_class_input_topic std_msgs/Float32 2.0
# ================================================================
# cd workspace/src
$ cs_create_pkg using_a_ros_library roscpp std_msgs std_srvs creating_a_ros_library
# cd workspace dir
# add cpp file and update CMakeLists.txt
$ catkin_make
```

### `2.5 动作服务器和动作客户端介绍` 中 记录下来的一些命令

```
# cd workspace/src
$ cs_create_pkg example_action_server roscpp actionlib
# add action/demo.action
# update package.xml
# cd workspace dir
$ catkin_make
# add cpp file and update CMakeLists.txt
$ catkin_make
# tty1
$ roscore
# tty2
$ source devel/setup.bash
$ rosrun example_action_server example_action_server
# tty3
$ source devel/setup.bash
$ rosrun example_action_server example_action_client
# tty4
$ source devel/setup.bash
$ rostopic echo example_action/goal 
```

timer_client & example_action_server_w_fdbk
```
# tty1
$ roscore
# tty2
$ rosrun rqt_console rqt_console
# tty3
$ source devel/setup.bash
$ rosrun example_action_server example_action_server_w_fdbk
# tty4
$ source devel/setup.bash
$ rosrun example_action_server timer_client
```

### `2.6 参数服务器介绍` 中 记录下来的一些命令

```
$ rosparam set /gains "p: 1.0
i: 2.0
d: 3.0"
$ rosparam list
$ rosparam get /gains/d
$ rosparam get /gains
$ rosparam dump param_dump
```

read_param_from_node

```
# cd workspace/src
$ cs_create_pkg example_param_server roscpp std_msgs
# add launch/jnt1_gains.yaml  launch/load_gains.launch
# cd workspace dir
# add cpp file and update CMakeLists.txt
$ catkin_make
# tty1
$ roscore
# tty2
$ roslaunch example_parameter_server load_gains.launch
$ rosrun example_parameter_server read_param_from_node 
$ rosparam delete /joint1_gains
$ rosrun example_parameter_server read_param_from_node 
```
