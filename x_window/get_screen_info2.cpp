#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <stdlib.h>
#include <iostream>
#include <stdarg.h>

typedef enum _name_kind {
    name_none = 0,
    name_string = (1 << 0),
    name_xid = (1 << 1),
    name_index = (1 << 2),
    name_preferred = (1 << 3),
} name_kind_t;

typedef struct {
    name_kind_t     kind;
    char          *string;
    XID           xid;
    int       index;
} name_t;

typedef struct _crtc crtc_t;
typedef struct _output  output_t;
typedef struct _transform transform_t;

struct _transform {
    XTransform      transform;
    const char      *filter;
    int       nparams;
    XFixed      *params;
};

struct _crtc {
    name_t      crtc;
    Bool      changing;
    XRRCrtcInfo     *crtc_info;

    XRRModeInfo     *mode_info;
    XRRPanning      *panning_info;
    int       x;
    int       y;
    Rotation      rotation;
    output_t      **outputs;
    int       noutput;
    transform_t     current_transform, pending_transform;
};

static Display *dpy;
static Window root;
static int screen = -1;
static XRRScreenResources  *res;
static int  minWidth, maxWidth, minHeight, maxHeight;

static void fatal(const char *format, ...)
{
    va_list ap;
  
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    exit(1);
    /*NOTREACHED*/
}

static void get_screen (bool current)
{
    XRRGetScreenSizeRange (dpy, root, &minWidth, &minHeight, &maxWidth, &maxHeight);

    if (current)
        res = XRRGetScreenResourcesCurrent (dpy, root);
    else 
        res = XRRGetScreenResources (dpy, root);
    if (!res) fatal ("could not get screen resources");
}

int main(int argc, char *agrv[])
{
    const char *display_name = NULL;

    dpy = XOpenDisplay(display_name);
    std::cout << "ScreenCount: " << ScreenCount(dpy) << std::endl;

    screen = DefaultScreen(dpy);

    root = RootWindow(dpy, screen);

    get_screen(true);
    printf ("Screen %d: minimum %d x %d, current %d x %d, maximum %d x %d\n",
        screen, minWidth, minHeight,
        DisplayWidth (dpy, screen), DisplayHeight(dpy, screen),
        maxWidth, maxHeight);


    return 0;
}

