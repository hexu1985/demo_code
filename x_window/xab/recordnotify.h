#ifndef RECORDNOTIFY_H
#define RECORDNOTIFY_H

#include <X11/X.h>
#include <X11/Xlib.h>

#include <X11/extensions/record.h>

#include "notify.h"

class RecordNotify : public Notify
{
private:
	Display *control_connection;
	Display *data_connection;

	XRecordContext context;
	XRecordClientSpec clients;
	XRecordRange ** range;
public:
	RecordNotify (App & app);
	~RecordNotify ();
	void run();

	static void callback (XPointer closure, XRecordInterceptData *recorded_data);
};

#endif
