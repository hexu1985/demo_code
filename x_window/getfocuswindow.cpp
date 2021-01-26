#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Display* dpy;

static void
Display_Window_Id(Window window)
{
  //printf("0x%lx ", window);
  if (!window) {
	printf("(null)");
  } else {
	if (window == DefaultRootWindow(dpy)) {
      printf("(the root window)");
	} else {
      XClassHint class_hint;
      if (XGetClassHint(dpy, window, &class_hint)) {
        if (class_hint.res_name) {
          XFree(class_hint.res_name);
        }
        if (class_hint.res_class) {
          printf("%s", class_hint.res_class);
          XFree(class_hint.res_class);
        }
      } else {
        Window parent_window, root_window;
        Window *children;
        unsigned int nchildren;
        if (XQueryTree(dpy, window, &root_window, &parent_window, &children, &nchildren)) {
          if (children) XFree(children);
          if (parent_window == root_window) {
            printf("(window without class hint)");
          } else {
            Display_Window_Id(parent_window);
            return;
          }
        } else {
          // most likely a BadWindow error
          printf("(x11 error)");
        }
      }
    }
  }
  printf("\n");
  fflush(stdout);

  return;
}

int handler(Display * error_display, XErrorEvent * error_event)
{
  if (error_event->error_code == BadWindow) {
    // safe to ignore, seemt to happen eg. during window manager replacement
    fprintf(stderr, "Ignoring BadWindow error.\n");
  } else {
    char buf[256];
    XGetErrorText(error_display, error_event->error_code, buf, 250);
    fprintf(stderr, "X11 Error: %s\n", buf);
    exit(1);
  }
  return 0;
}

int
main()
{
  dpy = XOpenDisplay(0);
  if (!dpy) {
    fprintf(stderr, "unable to open x11 display\n");
    exit(-1);
  }

  XSetErrorHandler(handler);

  Window focus_window = 0;
  while (1) {
    usleep(50000);
    Window win;
    int trash;
    if (XGetInputFocus(dpy, &win, &trash)) {
      if (win != focus_window) {
        focus_window = win;
        Display_Window_Id(focus_window);
      }
    } else {
      printf("(XGetInputFocus error)\n");
    }
  }
  XCloseDisplay(dpy);
  return 0;
}
