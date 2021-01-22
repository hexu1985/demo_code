#ifndef WIN_H
#define WIN_H

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/Xos.h>
#include <X11/extensions/XTest.h>


class Grab
{
private:
	Display *display;

	Window& window;
public:
	Grab(Display *display, Window &window);
	~Grab();
};

#endif
