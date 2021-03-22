/*
  * 下边是编译命令
  * gcc x11.c -o output -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
  */
 
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "x_monitor_info_query.hpp"
 
int main(void)
{
    Display *display;
    int screen;
    Window root, window;

    display = XOpenDisplay(NULL);
    if (!display)
    {
        fprintf(stderr, "Could not open display\n");
        exit(1);
    }

    screen = DefaultScreen(display);
    root = RootWindow(display, screen);

    window = DefaultRootWindow(display);
    if (0 > window)
    {
        fprintf(stderr, "Failed to obtain the root windows Id of the default screen of given display.\n");
        exit(1);
    }

    XWindowAttributes xwAttr;
    Status ret = XGetWindowAttributes(display, window, &xwAttr);
    int width = xwAttr.width;
    int height = xwAttr.height;
    // fprintf(stderr, "Current Width,Height %d,%d\n", width, height);
    {
        XMonitorInfoQuery query;
        query.print();
    }

    XSelectInput(display, window, ExposureMask |
        /* Add StructureNotifyMask to send us events
         *                          involving resizing of the window, etc. */
        StructureNotifyMask);

    XMapWindow(display, window);
 
    while (1){
        XEvent e;
        XNextEvent(display, &e);

        // Respond to ConfigureNotify, the type of event sent by the
        // server if the window is resized.
        if (e.type == ConfigureNotify){
            XConfigureEvent xce = e.xconfigure;

            /* This event type is generated for a variety of
               happenings, so check whether the window has been
               resized. */
            // fprintf(stderr, "New Width,Height %d,%d\n", xce.width, xce.height);
            XMonitorInfoQuery query;
            query.print();
        }
    }

    XCloseDisplay(display);

    return 0;
}
