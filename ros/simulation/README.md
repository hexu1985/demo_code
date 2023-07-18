


### `3.1 简单的2维机器人仿真器` 中 记录下来的一些命令

```
$ mkdir -p simulation/src
# cd simulation/src
$ git clone https://github.com/stdr-simulator-ros-pkg/stdr_simulator.git
$ cd ..
$ rosdep install --from-paths src --ignore-src --rosdistro $ROS_DISTRO
$ catkin_make
# after a successful build
source <your_catkin_ws>/devel/setup.bash
```

