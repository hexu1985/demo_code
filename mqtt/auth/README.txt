1) 配置mosquitto.conf, 增加如下配置:
allow_anonymous允许匿名: allow_anonymous false
password_file密码文件: password_file /home/hexu/pwfile
acl_file访问控制列表: acl_file /home/hexu/aclfile
2) 添加用户testuser:
$ mosquitto_passwd -c /home/hexu/pwfile testuser
3) 添加Topic和用户的关系, 修改acl_file文件:
user testuser
topic write hello/#

user testuser
topic read hello/#
4) 用户认证测试:
$ mosquitto -c /etc/mosquitto/mosquitto.conf -v
或
$ mosquitto -c /etc/mosquitto/mosquitto.conf -d
5) 启动mosquitto_sub
$ mosquitto_sub -h 127.0.0.1 -t hello -u testuser -P testpassword
6) 启动mosquitto_pub
$ mosquitto_pub -h 127.0.0.1 -t hello -u testuser -P testpassword -m "hello world"
7) 编译并运行async_publish.cpp和async_subscribe.cpp
$ mkdir build
$ cmake build 
$ cmake ..
$ make
