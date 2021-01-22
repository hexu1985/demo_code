#include "grabnotify.h"

#include <iostream>

#include "grab.h"
#include "exc.h"

#include "app.h"

using namespace std;


GrabNotify::GrabNotify(App &app) :
	Notify(app)
{
	display = app.getDisplay();

	if (display==0) throw "app did not pass display";

	attrib.override_redirect= True;

	window= XCreateWindow(display,DefaultRootWindow(display),
		0,0,1,1,0,CopyFromParent,InputOnly,CopyFromParent,
		CWOverrideRedirect,&attrib);

	if (window == BadAlloc) throw "could not allocate window";
	else if (window == BadColor) throw "could not get color for window";
	else if (window == BadCursor) throw "could not get cursor for window";
	else if (window == BadMatch) throw "could not match window";
	else if (window == BadPixmap) throw "could not get pixmap for window";
	else if (window == BadValue) throw "numeric value of request out of range";
	else if (window == BadWindow) throw "could not create window";

	if (XSelectInput(display,window,KeyPressMask|KeyReleaseMask)
			== BadWindow)
		throw "could not select input";

	if (XMapRaised(display,window)
			== BadWindow)
		throw "could not map window";
}

GrabNotify::~GrabNotify()
{
	XDestroyWindow(display, window);
}

void GrabNotify::run()
{
	while (true) runOnce();
}

void GrabNotify::runOnce()
{
	XEvent ev;

	try {
		Grab g (display, window);

		while (true) // until KeyPress appeared
		{
			XNextEvent(display,&ev);

#ifdef DEBUG
			wcout << "GrabEvent: " << event_type(ev.type)
				<< "\tKeycode:" << ev.xkey.keycode
				<< "\tQueued: "
				<< XEventsQueued(display,QueuedAlready)
				<< "\tInput: " << input
				<< endl;
#endif

			// avoid endless loop of key repitition
			if (XEventsQueued(display,QueuedAlready) != 0) continue;

			break;
		}

	} catch (grab_exception const & ge)
	{
		wcout << ge.what() << endl;
		return;
	}

	// keypress event must be here to be a subtype of notify
	if (ev.type == KeyPress) app.forward_key_press(ev.xkey.keycode);
	// if (ev.type == KeyRelease) forward_key_release(ev.xkey.keycode);

	app.processEvent(ev);

	if (app.quit()) throw "quit because of signal";
}
