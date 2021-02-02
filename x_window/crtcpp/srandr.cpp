#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xrender.h>  /* we share subpixel information */
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include <math.h>

/* subpixel order */
static const char *order[6] = {
    "unknown",
    "horizontal rgb",
    "horizontal bgr",
    "vertical rgb",
    "vertical bgr",
    "no subpixels"};


static Window	root;
int    event_base, error_base;
int    major, minor;
int  screen = -1;

int process_events(Display * dpy)
{
    XEvent	event;

    XSelectInput (dpy, root, StructureNotifyMask);
    XRRSelectInput (dpy, root, RRScreenChangeNotifyMask);
    XSync(dpy, False);
    XRRScreenChangeNotifyEvent *sce;    
    int spo;
    while (1) {
        XNextEvent(dpy, (XEvent *) &event);
        printf ("Event received, type = %d\n", event.type);

        if (event.type == ConfigureNotify)
            printf("Received ConfigureNotify Event!\n");

        switch (event.type - event_base) {
            case RRScreenChangeNotify:
                sce = (XRRScreenChangeNotifyEvent *) &event;

                printf("Got a screen change notify event!\n");
                printf(" window = %d\n root = %d\n size_index = %d\n rotation %d\n", 
                        (int) sce->window, (int) sce->root, 
                        sce->size_index,  sce->rotation);
                printf(" timestamp = %ld, config_timestamp = %ld\n",
                        sce->timestamp, sce->config_timestamp);
                printf(" Rotation = %x\n", sce->rotation);
                printf(" %d X %d pixels, %d X %d mm\n",
                        sce->width, sce->height, sce->mwidth, sce->mheight);
                printf("Display width   %d, height   %d\n",
                        DisplayWidth(dpy, screen), DisplayHeight(dpy, screen));
                printf("Display widthmm %d, heightmm %d\n", 
                        DisplayWidthMM(dpy, screen), DisplayHeightMM(dpy, screen));
                spo = sce->subpixel_order;
                if ((spo < 0) || (spo > 5))
                    printf ("Unknown subpixel order, value = %d\n", spo);
                else 
                    printf ("new Subpixel rendering model is %s\n", order[spo]);
                break;
            default:
                if (event.type != ConfigureNotify) 
                    printf("unknown event received, type = %d!\n", event.type);
        }
    }
    return EXIT_SUCCESS;
}

int main() 
{
    Display *dpy;
    char *display_name = NULL;

    dpy = XOpenDisplay (display_name);

    if (dpy == NULL) {
        fprintf (stderr, "Can't open display %s\n", XDisplayName(display_name));
        exit (1);
    }

    if (screen < 0)
        screen = DefaultScreen (dpy);
    if (screen >= ScreenCount (dpy)) {
        fprintf (stderr, "Invalid screen number %d (display has %d)\n",
                screen, ScreenCount (dpy));
        exit (1);
    }

    root = RootWindow (dpy, screen);

    if (!XRRQueryExtension (dpy, &event_base, &error_base) ||
            !XRRQueryVersion (dpy, &major, &minor))
    {
        fprintf (stderr, "RandR extension missing\n");
        exit (1);
    }

    return process_events(dpy);
}
