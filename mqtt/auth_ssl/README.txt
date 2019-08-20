1) ssl配置: 参考../ssl/README.txt的1)和2)
2) auth配置: 参考../auth/README.txt的1)和2)和3)
3) 启动mosquitto
$ mosquitto -c ./mosquitto.conf -v
或
$ mosquitto -c /etc/mosquitto/mosquitto.conf -d
5) 启动mosquitto_sub
$ mosquitto_sub -h 10.4.98.74 -p 8883 -t hello -u testuser -P testpassword --cafile /home/hexu/TLSDir/ca/ca.crt
6) 启动mosquitto_pub
$ mosquitto_pub -h 10.4.98.74 -p 8883 -t hello -u testuser -P testpassword -m "hello world" --cafile /home/hexu/TLSDir/ca/ca.crt
7) 编译并运行ssl_publish.cpp和ssl_subscribe.cpp: 参考../ssl/README.txt的6)和7)
