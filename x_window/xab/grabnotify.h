#ifndef GRABNOTIFY_H
#define GRABNOTIFY_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xos.h>

#include "notify.h"

class GrabNotify : public Notify
{
private:
	Display *display;

	Window window;
	XSetWindowAttributes attrib;

public:
	GrabNotify(App &app);
	~GrabNotify();

	void run();

private:
	void runOnce();
};

#endif
