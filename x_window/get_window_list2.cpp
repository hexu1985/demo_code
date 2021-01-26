#include <xcb/xcb.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xinerama.h>
#include <iostream>

void print_window_info(Display *display, XID &window) 
{
    XTextProperty property;
    XGetWMName(display, window, &property);
    int cnt = 0;
    char **list = nullptr;
    Xutf8TextPropertyToTextList(display, &property, &list, &cnt);
    std::string name(cnt ? (char *)list[0] : "");
    std::cout << "window id: " << (int) window << std::endl;
    std::cout << "window name: " << name << std::endl;

    XWindowAttributes wndattr;
    XGetWindowAttributes(display, window, &wndattr);
    std::cout << "window attr(x,y,width,height): "
              << "(" << wndattr.x << ","
              << wndattr.y << ","
              << wndattr.width << ","
              << wndattr.height << ")" << std::endl;
}

int main()
{
    Display *display = XOpenDisplay(NULL);

    // _NET_CLIENT_LIST has oldest-to-newest initial mapping order
    // _NET_CLIENT_LIST_STACKING has bottom-to-top stacking order
    Atom atom = XInternAtom(display, "_NET_CLIENT_LIST_STACKING", true);
    Atom actual_type;
    int format;
    unsigned long num_items, bytes_after;
    unsigned char *data = 0;
    int status = XGetWindowProperty(
            display, XDefaultRootWindow(display), atom, 0L, (~0L), false,
            AnyPropertyType, &actual_type, &format, &num_items, &bytes_after, &data);
    if (status >= Success && num_items) {
        XID *array = (XID *)data;
        for (unsigned long i = 0; i < num_items; i++) {
            XID &w = array[i];
            std::cout << "======================" << i << "=====================" << std::endl;
            print_window_info(display, w);
        }
        XFree(data);
    }
    XCloseDisplay(display);

    return 0;
}

