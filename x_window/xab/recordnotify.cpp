#include "recordnotify.h"

#include <iostream>

#include "app.h"

using namespace std;


/**Notify the app using XRecord.

  For Information about XRecord,
  see http://www.x.org/docs/Xext/recordlib.pdf

  Example see http://blogs.sun.com/yongsun/entry/my_first_blog_in_sun

  */
RecordNotify::RecordNotify (App & app) :
	Notify(app)
{
	control_connection = XOpenDisplay(0);
	if (control_connection==0) throw "cannot open control_connection in RecordNotify";

	data_connection = XOpenDisplay(0);
	if (data_connection==0) throw "cannot open data_connection in RecordNotify";

	XSynchronize(control_connection, True);

	clients = XRecordAllClients;

	range = new XRecordRange*[1];
	range[0] = XRecordAllocRange();

	if (range == 0) throw "could not alloc range in RecordNotify";

	range[0]->device_events.first=KeyPress;
	range[0]->device_events.last=KeyRelease; // MotionNotify to be xmacrorec2 compatible

	context = XRecordCreateContext (control_connection, //see page 5
			XRecordFromServer | XRecordFromClientSequence,  //2.1
			&clients, //2.2
			1,
			range,
			1
			);

	if (context==0) throw "cannot create context in RecordNotify";
}

RecordNotify::~RecordNotify ()
{
	cerr << "Close XRecord Context" << endl;

	XRecordFreeContext (control_connection, context);

	XFree (range[0]);
	delete [] range;


	XCloseDisplay(control_connection);
	XCloseDisplay(data_connection);
}

void RecordNotify::run()
{
	Status s = XRecordEnableContext (data_connection, //see page 8
			context, callback,
			reinterpret_cast<XPointer>(this));
	if (s==0) throw "could not enable context";
}

void RecordNotify::callback (XPointer closure, XRecordInterceptData *recorded)
{
	RecordNotify *that = reinterpret_cast<RecordNotify*> (closure);

	unsigned char *ud1 = (unsigned char *)recorded->data;
	unsigned short *ud2 = (unsigned short *)recorded->data;
	short *d2 = (short *)recorded->data;
	unsigned int *ud4 = (unsigned int *)recorded->data;

	if (recorded->category==XRecordStartOfData) cerr << "Got Start Of Data" << endl;
	if (recorded->category==XRecordEndOfData) cerr << "Got End Of Data" << endl;
	if (recorded->category!=XRecordFromServer)
	{
		cerr << "Skipping..." << endl;
		goto returning;
	}
	if (recorded->client_swapped==True) cerr << "Client is swapped!!!" << endl;

	XEvent ev;

	ev.type = ud1[0]&0x7F;

	ev.xkey.type = ud1[0]&0x7F;
	ev.xkey.serial = ud2[1];
	ev.xkey.send_event = (unsigned int)(ud1[0]>>8);
	ev.xkey.display = that->app.getDisplay();
	ev.xkey.window = ud4[3];
	ev.xkey.root = ud4[2];
	ev.xkey.subwindow = ud4[4];
	ev.xkey.time = ud4[1];
	ev.xkey.x = d2[12];
	ev.xkey.y = d2[13];
	ev.xkey.x_root = d2[10];
	ev.xkey.y_root = d2[11];
	ev.xkey.state = d2[14];
	ev.xkey.keycode = ud1[1];
	ev.xkey.same_screen = ud1[30];

	that->app.processEvent(ev);

returning:
	XRecordFreeData (recorded);

	if (that->app.quit())
	{
		cerr << "about to quit" << endl;
		XRecordDisableContext (that->control_connection, that->context);
	}
}

