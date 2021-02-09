/*
  * 下边是编译命令
  * gcc x11.c -o output -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
  */
 
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void)
{
    Display *display;
    Window window;
    XEvent event;
//    char *msg = "你好 ,这是一个测试窗口!";
    char *msg = "hello world! this is a test window";
    int s;
 
    /* 与Xserver建立连接 */
    display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
 
 		
    s = DefaultScreen(display);
 
    /* 创建一个窗口 */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 200, 200, 1,
                           BlackPixel(display, s), WhitePixel(display, s));
 
    /* 选择一种感兴趣的事件进行监听 */
    XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);
 
    /* 显示窗口 */
    XMapWindow(display, window);
 
    /* 事件遍历 */
    for (;;)
    {
        XNextEvent(display, &event);
 
        /* 绘制窗口或者重新绘制 */
        if (event.type == Expose)
        {
            printf("receive Expose event\n");
            XFillRectangle(display, window, DefaultGC(display, s), 20, 20, 10, 10);
            XDrawString(display, window, DefaultGC(display, s), 50, 50, msg, strlen(msg));
        }

        if (event.type == ConfigureNotify){
            XConfigureEvent xce = event.xconfigure;

            /* This event type is generated for a variety of
               happenings, so check whether the window has been
               resized. */
            fprintf(stderr, "New Width,Height %d,%d\n", xce.width, xce.height);
        }

        /* 当检测到键盘按键,退出消息循环 */
        if (event.type == KeyPress)
            break;
    }
 
    /* 关闭与Xserver服务器的连接 */
    XCloseDisplay(display);
 
    return 0;
 }
