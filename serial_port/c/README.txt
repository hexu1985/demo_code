// 模拟终端测试方法

1) 打开模拟终端
# socat -d -d pty,raw,echo=0 pty,raw,echo=0
返回结果:
2018/04/12 12:43:08 socat[2955] N PTY is /dev/pts/2
2018/04/12 12:43:08 socat[2955] N PTY is /dev/pts/3
2018/04/12 12:43:08 socat[2955] N starting data transfer loop with FDs [5,5] and [7,7]

2) 查看终端的波特率:
# stty -a -F /dev/pts/2
返回结果:
peed 38400 baud; rows 0; columns 0; line = 0;
intr = ^C; quit = ^\; erase = ^?; kill = ^U; eof = ^D; eol = <undef>; eol2 = <undef>; swtch = <undef>; start = ^Q;
stop = ^S; susp = ^Z; rprnt = ^R; werase = ^W; lnext = ^V; discard = ^O; min = 1; time = 0;
-parenb -parodd -cmspar cs8 -hupcl -cstopb cread -clocal -crtscts
-ignbrk -brkint -ignpar -parmrk -inpck -istrip -inlcr -igncr -icrnl -ixon -ixoff -iuclc -ixany -imaxbel -iutf8
-opost -olcuc -ocrnl onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0
-isig -icanon iexten -echo echoe echok -echonl -noflsh -xcase -tostop -echoprt echoctl echoke -flusho -extproc

3) 编译并运行tty_read2
# make
# ./tty_read2 /dev/pts/2 38400

4) 模拟数据发送
# echo "test" > /dev/pts/3
