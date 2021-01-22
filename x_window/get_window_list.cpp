#include <xcb/xcb.h>
#include <X11/Xlib.h>
#include <iostream>

// 窗口属性
#if 0
typedef struct {
    int x, y;                     /* location of window */
    int width, height;            /* width and height of window */
    int border_width;             /* border width of window */
    int depth;                    /* depth of window */
    Visual *visual;               /* the associated visual structure */
    Window root;                  /* root of screen containing window */
    int class;                    /* InputOutput, InputOnly*/
    int bit_gravity;              /* one of the bit gravity values */
    int win_gravity;              /* one of the window gravity values */
    int backing_store;            /* NotUseful, WhenMapped, Always */
    unsigned long backing_planes; /* planes to be preserved if possible */
    unsigned long backing_pixel;  /* value to be used when restoring planes */
    Bool save_under;              /* boolean, should bits under be saved? */
    Colormap colormap;            /* color map to be associated with window */
    Bool map_installed;           /* boolean, is color map currently installed*/
    int map_state;                /* IsUnmapped, IsUnviewable, IsViewable */
    long all_event_masks;         /* set of events all people have interest in*/
    long your_event_mask;         /* my event mask */
    long do_not_propagate_mask;   /* set of events that should not propagate */
    Bool override_redirect;       /* boolean value for override-redirect */
    Screen *screen;               /* back pointer to correct screen */
} XWindowAttributes;
#endif



int main()
{
    auto display = XOpenDisplay(nullptr);
    auto root_window = DefaultRootWindow(display);

    Window root_return, parent_return;
    Window * child_list = nullptr;
    unsigned int child_num = 0;
    XQueryTree(display, root_window, &root_return, &parent_return, &child_list, &child_num);

    std::cout << "window[#]: (x, y, width, height)" << std::endl;
    for(unsigned int i = 0; i < child_num; ++i) {
        auto window = child_list[i];
        XWindowAttributes attrs;
        XGetWindowAttributes(display, window, &attrs);

        std::cout << "window[" << i << "]: (" 
                  << attrs.x << ", "  << attrs.y << ", " << attrs.width << ", " << attrs.height 
                  << ")" << std::endl; 
    }

    XFree(child_list);
    XCloseDisplay(display);

    return 0;
}
