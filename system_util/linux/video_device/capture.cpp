#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <string.h>
#include <sys/mman.h>

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
    vfmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG; //设置为mjpg格式，则我可以直接写入文件保存，YUYV格式保存后需要转换格式才能查看

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

    //映射
    unsigned char *mptr[4];//保存映射后用户空间的首地址
    unsigned int size[4];
    struct v4l2_buffer mapbuffer;
    //初始化type和index
    mapbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    for(int i = 0; i <4;i++) {
        mapbuffer.index = i;
        ret = ioctl(fd,VIDIOC_QUERYBUF,&mapbuffer); //从内核空间中查询一个空间作映射
        if (ret < 0)
        {
            perror("查询内核空间失败");
        }
        //映射到用户空间
        mptr[i] = (unsigned char *)mmap(NULL,mapbuffer.length,PROT_READ|PROT_WRITE,MAP_SHARED,fd,mapbuffer.m.offset);
        size[i] = mapbuffer.length; //保存映射长度用于后期释放
        //查询后通知内核已经放回
        ret = ioctl(fd,VIDIOC_QBUF,&mapbuffer); 
        if (ret < 0)
        {
            perror("放回失败");
        }
    }
    //开始采集
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd,VIDIOC_STREAMON,&type); 
    if (ret < 0)
    {
        perror("开启失败");
    }
    //从队列中提取一帧数据
    struct v4l2_buffer readbuffer;
    readbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; //每个结构体都需要设置type为这个参赛要记住
    ret = ioctl(fd,VIDIOC_DQBUF,&readbuffer); 
    if (ret < 0)
    {
        perror("读取数据失败");
    }

    const char* jpg_file = "result.jpg";
    if (argc > 2) {
        jpg_file = argv[2];
    }
    FILE *file=fopen(jpg_file, "w+");  //打开一个文件
    fwrite(mptr[readbuffer.index],readbuffer.length,1,file);//写入文件
    fclose(file);    //写入完成，关闭文件

    //通知内核使用完毕
    ret = ioctl(fd, VIDIOC_QBUF, &readbuffer);
    if(ret < 0)
    {
        perror("放回队列失败");
    }

    //停止采集
    ret = ioctl(fd,VIDIOC_STREAMOFF,&type);

    //释放映射
    for (int i=0; i<4; i++) {
        munmap(mptr[i], size[i]);
    }

    close(fd); //关闭文件

    return 0;
}

