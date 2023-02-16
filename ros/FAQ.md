
1. rosdep init失败 
    - 报错信息
        ```
        $ sudo rosdep init
        ERROR: cannot download default sources list from:
        https://raw.githubusercontent.com/ros/rosdistro/master/rosdep/sources.list.d/20-default.list
        Website may be down.
        ```
    - 解决方法
        + 打开网址：https://site.ip138.com ，在其中搜索raw.githubusercontent.com ，可看到当前解析的IP地址。
        + 打开终端输入指令sudo gedit /etc/hosts，输入用户密码，即可编辑此文档，在其中加入以下语句，其中的151.101.76.133就是上一步中查到的IP地址之一，然后保存并关闭此文档。
            ```
            185.199.110.133 raw.githubusercontent.com
            ```

2. rosdep init失败 
    - 报错信息
        ```
        $ sudo rosdep init
        ERROR: default sources list file already exists:
                /etc/ros/rosdep/sources.list.d/20-default.list
        Please delete if you wish to re-initialize
        ```

    - 解决方法

        ```
        $ sudo rm /etc/ros/rosdep/sources.list.d/20-default.list
        ```
