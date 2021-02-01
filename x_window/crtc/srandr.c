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

int process_events(Display * dpy)
{
	XEvent ev;

	XRRSelectInput(dpy, DefaultRootWindow(dpy), RROutputChangeNotifyMask);
	XSync(dpy, False);
//	XSetIOErrorHandler((XIOErrorHandler) error_handler);
	while (1) {
		if (!XNextEvent(dpy, &ev)) {
            printf("get some event\n");
		}
	}
	return EXIT_SUCCESS;
}

int main() 
{
    Display	*dpy;
    int	screen = -1;
    char          *display_name = NULL;
    int		event_base, error_base;
    int		major, minor;

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

    if (!XRRQueryExtension (dpy, &event_base, &error_base) ||
            !XRRQueryVersion (dpy, &major, &minor))
    {
        fprintf (stderr, "RandR extension missing\n");
        exit (1);
    }

    return process_events(dpy);
}
