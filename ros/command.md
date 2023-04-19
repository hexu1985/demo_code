
- rosmsg show
    ```
    $ rosmsg show std_msgs/Float64
    ```

- rostopic
    + rostopic list
    + rostopic hz <topic1>
    + rostopic bw <topic1>
    + rostopic info <topic1>
    + rostopic echo <topic1>
    ```
    $ rostopic pub -r 10 force_cmd std_msgs/Float64 0.1
    ```

- rosnode list

- rqt_graph

- roslaunch
    ```
    $ roslaunch my_minimal_nodes my_minimal_nodes.launch
    ```

- rosbag 
    + rosbag record <topic1>
    + rosbag play <fname.bag>

- rqt_plot velocity/data
