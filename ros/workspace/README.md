


- `1.2 编写ROS节点` 中 记录下来的一些命令

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

- `1.3.1 用catkin_simple简化CmakeLists.txt` 中 记录下来的一些命令

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
```
