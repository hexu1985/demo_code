#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>

#include <iostream>

int main() 
{
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        std::cout << "XOpenDisplay failed" << std::endl;
        return -1;
    }

    int nmonitors = 0;
    XineramaScreenInfo *screen = XineramaQueryScreens(display, &nmonitors);
    if (!screen) {
        XCloseDisplay(display);
        std::cout << "XineramaQueryScreens failed" << std::endl;
        return -1;
    }

    std::cout << "nmonitors: " << nmonitors << std::endl;
    for (auto i = 0; i < nmonitors; i++) {
        std::cout << "screen " << i << std::endl;
        std::cout << "\tpos_x: " << (int)screen[i].x_org << std::endl;
        std::cout << "\tpos_y: " << (int)screen[i].y_org << std::endl;
        std::cout << "\twidth: " << (int)screen[i].width << std::endl;
        std::cout << "\theight: " << (int)screen[i].height << std::endl;
        std::cout << std::endl;
    }

    XFree(screen);
    XCloseDisplay(display);

    return 0;
}

