#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
	const char* dev = "/dev/video0";
    if (argc > 1) {
        dev = argv[1];
    }
    int fd = open(dev,O_RDWR);
    if (fd < 0)
    {
        perror("打开设备失败");
        return -1;
    }

    //获取摄像头支持格式 ioctl(文件描述符,命令，与命令对应的结构体)
    struct v4l2_format vfmt;

    vfmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; //摄像头采集
    vfmt.fmt.pix.width = 640; //设置摄像头采集参数，不可以任意设置
    vfmt.fmt.pix.height = 480;
    vfmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV; //设置视频采集格式 ，根据上一布测得
    
    int ret = ioctl(fd,VIDIOC_S_FMT,&vfmt);
    if (ret < 0)
    {
        perror("设置格式失败1");
    }

    //申请内核空间
    struct v4l2_requestbuffers reqbuffer;
    reqbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuffer.count = 4; //申请4个缓冲区
    reqbuffer.memory = V4L2_MEMORY_MMAP;  //映射方式

    ret = ioctl(fd,VIDIOC_REQBUFS,&reqbuffer);
    if (ret < 0)
    {
        perror("申请空间失败");
    }
   
    close(fd);
    return 0;
}

