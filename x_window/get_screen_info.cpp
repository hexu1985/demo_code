#include <X11/Xlib.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char *agrv[])
{
    XSetWindowAttributes winattrs;
    int swidth;/*屏幕宽度*/
    int sheight;/*屏幕高度*/
    int winmask;
    Display *display;
    int screen;
    Window window;

    display = XOpenDisplay(getenv("DISPLAY"));
    screen = DefaultScreen(display);
    swidth = DisplayWidth(display, screen);/*获取屏幕宽度*/
    sheight = DisplayHeight(display, screen);/*获取屏幕高度*/
    int scount = ScreenCount(display);

    std::cout << "screen count: " << scount << std::endl;
    std::cout << "default screen index: " << screen << std::endl;
    std::cout << "screen width: " << swidth << std::endl;
    std::cout << "screen height: " << sheight << std::endl;

    return 0;
}
