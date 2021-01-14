#include <xcb/xcb.h>
#include <X11/Xlib.h>
#include <iostream>

int main()
{
    auto display = XOpenDisplay(nullptr);
    auto root_window = DefaultRootWindow(display);

    Window root_return, parent_return;
    Window * child_list = nullptr;
    unsigned int child_num = 0;
    XQueryTree(display, root_window, &root_return, &parent_return, &child_list, &child_num);

    for(unsigned int i = 0; i < child_num; ++i) {
        auto window = child_list[i];
        XWindowAttributes attrs;
        XGetWindowAttributes(display, window, &attrs);

        std::cout << "#" << i <<":" << "(" << attrs.width << ", " << attrs.height << ")" << std::endl;
    }

    XFree(child_list);
    XCloseDisplay(display);

    return 0;
}
