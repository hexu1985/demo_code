#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xrender.h>	/* we share subpixel information */
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include <math.h>

const char* RRNotifySubtypeToString(int subtype) {
    switch (subtype) {
        case RRNotify_OutputChange:
            return "RRNotify_OutputChange";
        case RRNotify_CrtcChange:
            return "RRNotify_CrtcChange";
        case RRNotify_OutputProperty:
            return "RRNotify_OutputProperty";
        default:
            return "Unknown RRNotify";
    }
}

int		rr_event_base_, rr_error_base_;
int		major, minor;

int process_events(Display * dpy)
{
	XEvent ev;

	XRRSelectInput(dpy, DefaultRootWindow(dpy), RRScreenChangeNotifyMask | RROutputChangeNotifyMask);
	XSync(dpy, False);
//	XSetIOErrorHandler((XIOErrorHandler) error_handler);
	while (1) {
		if (!XNextEvent(dpy, &ev)) {
			XEvent* xevent = &ev;
			XRRNotifyEvent *aevent = (XRRNotifyEvent*) (xevent);
            fprintf(stderr, "some event get: %d\n", (int) xevent->type);
			if (xevent->type == rr_event_base_ + RRScreenChangeNotify ||
					xevent->type == rr_event_base_ + RRNotify) {
				switch (xevent->type - rr_event_base_) {
					case RRScreenChangeNotify:
						fprintf(stderr, "RRScreenChangeNotify event received.\n");
						XRRUpdateConfiguration(xevent);
						break;
					case RRNotify:
						fprintf(stderr, "%s event received.\n", RRNotifySubtypeToString(aevent->subtype));
						break;
					default:
						fprintf(stderr, "Unknown GDK event received.\n");
				}
            }
		}
	}
	return EXIT_SUCCESS;
}

int main() 
{
    Display	*dpy;
    int	screen = -1;
    char          *display_name = NULL;

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

    if (!XRRQueryExtension (dpy, &rr_event_base_, &rr_error_base_) ||
            !XRRQueryVersion (dpy, &major, &minor))
    {
        fprintf (stderr, "RandR extension missing\n");
        exit (1);
    }

    return process_events(dpy);
}
