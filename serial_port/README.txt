// 用socat在linux下虚拟串口(终端)

1) 安装socat
# sudo apt-get install socat

2) 创建虚拟串口(终端)
//# socat -d -d pty,raw,echo=0 pty,raw,echo=0
# socat -d -d PTY PTY
返回结果:
2018/04/12 10:25:07 socat[664] N PTY is /dev/pts/2
2018/04/12 10:25:07 socat[664] N PTY is /dev/pts/3
2018/04/12 10:25:07 socat[664] N starting data transfer loop with FDs [5,5] and [7,7]

3) 测试虚拟串口(终端)
# cat < /dev/pts/2
# echo "Test" > /dev/pts/3
