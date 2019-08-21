1) 在指定目录下(自己选定)执行makefile.sh
# 我这里的示例是
$ mkdir -p /home/hexu/TLSDir
$ cp makefile.sh /home/hexu/TLSDir
$ cd /home/hexu/TLSDir
# 修改makefile.sh中的SERVER_HOST, CLIENT_HOST
$ ./makefile.sh
2) 修改mosquitto.conf中的cafile, certfile和keyfile  
注意, 变量名和值之间要用空格隔开, 不要用tab键, 否则会报:
Error: Unknown configuration variable "cafile ..."
之类的错误
而且小心文件路径后不要有多余的空格.
3) 启动mosquitto
$ mosquitto -c ./mosquitto.conf -v
或
$ mosquitto -c /etc/mosquitto/mosquitto.conf -d
4) 启动mosquitto_sub
$ mosquitto_sub -h 10.4.98.74 -p 8883 -t "/plant/peanut/UpdateTemperature" --cafile /home/hexu/TLSDir/ca/ca.crt --cert /home/hexu/TLSDir/client/client.crt --key /home/hexu/TLSDir/client/client.key
# --cert和--key对应的参数可以省略, 即
$ mosquitto_sub -h 10.4.98.74 -p 8883 -t "/plant/peanut/UpdateTemperature" --cafile /home/hexu/TLSDir/ca/ca.crt 
5) 启动mosquitto_pub
$ mosquitto_pub -h 10.4.98.74 -p 8883 -t "/plant/peanut/UpdateTemperature" -m "temperature:15" --cafile /home/hexu/TLSDir/ca/ca.crt --cert /home/hexu/TLSDir/client/client.crt --key /home/hexu/TLSDir/client/client.key
# --cert和--key对应的参数可以省略, 即
$ mosquitto_pub -h 10.4.98.74 -p 8883 -t "/plant/peanut/UpdateTemperature" -m "temperature:15" --cafile /home/hexu/TLSDir/ca/ca.crt 
6) 编译并运行ssl_publish.cpp和ssl_subscribe.cpp
$ mkdir build
$ cmake build 
$ cmake ..
$ make
7) ssl_publish.cpp和ssl_subscribe.cpp中KEY_STORE的说明:
const std::string KEY_STORE				{ "/home/hexu/TLSDir/client/client.pem" };
client.pem里包含client.key和client.crt的内容, 通过如下方式生成:
$ cat /home/hexu/TLSDir/client/
$ cat client.key client.crt > client.pem
