/***************************************************************************** 
 *
 * Heavily based on
 * xmacrorec2 - a utility for recording X mouse and key events.
 * written by Gabor Keresztfalvi <keresztg@mail.com>
 *
 ****************************************************************************/

/***************************************************************************** 
 * Includes
 ****************************************************************************/
#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/extensions/record.h>

#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <iomanip>

#include "recordasyncnotify.h"

#include "app.h"

using namespace std;

/***************************************************************************** 
 * The delay in milliseconds when sending events to the remote display
 ****************************************************************************/
const int DefaultDelay = 10;

/***************************************************************************** 
 * The multiplier used fot scaling coordinates before sending them to the
 * remote display. By default we don't scale at all
 ****************************************************************************/
const float DefaultScale = 1.0;

/***************************************************************************** 
 * Globals...
 ****************************************************************************/
int   Delay = DefaultDelay;
float Scale = DefaultScale;

/***************************************************************************** 
 * Key used for quitting the application.
 ****************************************************************************/
unsigned int QuitKey;
bool HasQuitKey = false;

/***************************************************************************** 
 * Private data used in eventCallback.
 ****************************************************************************/
typedef struct
{
	int Status1, Status2, x, y, mmoved, doit;
	unsigned int QuitKey;
	Display *LocalDpy, *RecDpy;
	XRecordContext rc;
	App * app;
	XEvent ev;
} Priv;



RecordAsyncNotify::RecordAsyncNotify(App & app) :
	Notify(app)
{}

RecordAsyncNotify::~RecordAsyncNotify()
{}

Display * localDisplay () {

  // open the display
  Display * D = XOpenDisplay ( 0 );

  // did we get it?
  if ( ! D ) {
	// nope, so show error and abort
	cerr << "Could not open display \"" << XDisplayName ( 0 )
		 << "\", aborting." << endl;
	exit ( EXIT_FAILURE );
  }

  // return the display
  return D;
}

/****************************************************************************/
/*! Scales the passed coordinate with the given saling factor. the factor is
    either given as a commandline argument or it is 1.0.
*/
/****************************************************************************/
int scale (const int Coordinate) {

  // perform the scaling, all in one ugly line
  return (int)( (float)Coordinate * Scale );
}


#ifdef DEBUG
#define DBG cerr << "type: " << type << " serial: " << seq << endl; \
		cerr << "send_event: " << (unsigned int)(ud1[0]>>8) << endl; \
		cerr << "window:  " << hex << wevent << " root: " << wroot << endl; \
		cerr << "subwindow:  " << wchild << " time: " << dec << tstamp << endl; \
		cerr << "x:  " << eventx << " y: " << eventy << endl; \
		cerr << "x_root:  " << rootx << " y_root: " << rooty << endl; \
		cerr << "state:  " << kstate << " detail: " << detail << endl; \
		cerr << "same_screen:  " << samescreen << endl << "------" << endl
#else
#define DBG
#endif

void eventCallback(XPointer priv, XRecordInterceptData *d)
{
  Priv *p=(Priv *) priv;
  unsigned int *ud4, tstamp, wroot, wevent, wchild, type, detail;
  unsigned char *ud1, type1, detail1, samescreen;
  unsigned short *ud2, seq;
  short *d2, rootx, rooty, eventx, eventy, kstate;

  if (d->category==XRecordStartOfData) cerr << "Got Start Of Data" << endl;
  if (d->category==XRecordEndOfData) cerr << "Got End Of Data" << endl;
  if (d->category!=XRecordFromServer || p->doit==0)
  {
	cerr << "Skipping..." << endl;
  	goto returning;
  }
  if (d->client_swapped==True) cerr << "Client is swapped!!!" << endl;
  ud1=(unsigned char *)d->data;
  ud2=(unsigned short *)d->data;
   d2=(short *)d->data;
  ud4=(unsigned int *)d->data;

  type1=ud1[0]&0x7F; type=type1;
  detail1=ud1[1]; detail=detail1;
  seq=ud2[1];
  tstamp=ud4[1];
  wroot=ud4[2];
  wevent=ud4[3];
  wchild=ud4[4];
  rootx=d2[10];
  rooty=d2[11];
  eventx=d2[12];
  eventy=d2[13];
  kstate=d2[14];
  samescreen=ud1[30];

  if (p->Status1)
  {
	  p->Status1--;
	  if (type==KeyRelease)
	  {
		cerr << "- Skipping stale KeyRelease event. " << p->Status1 << endl;
		goto returning;
	  } else p->Status1=0;
  }
  if (p->x==-1 && p->y==-1 && p->mmoved==0 && type!=MotionNotify)
  {
  	cerr << "- Please move the mouse before any other event to synchronize pointer" << endl;
  	cerr << "  coordinates! This event is now ignored!" << endl;
  	goto returning;
  }
  // what did we get?
  switch (type) {
    case ButtonPress:
	  // button pressed, create event
		DBG;
	  if (p->mmoved)
	  {
		cout << "MotionNotify " << p->x << " " << p->y << endl;
		p->mmoved=0;
	  }
	  if (p->Status2<0) p->Status2=0;
	  p->Status2++;
	  cout << "ButtonPress " << detail << endl;
      break;

    case ButtonRelease:
	  // button released, create event
		DBG;
	  if (p->mmoved)
	  {
		cout << "MotionNotify " << p->x << " " << p->y << endl;
		p->mmoved=0;
	  }
	  p->Status2--;
	  if (p->Status2<0) p->Status2=0;
	  cout << "ButtonRelease " << detail << endl;
	  break;

	case MotionNotify:
	  // motion-event, create event
		DBG;
	  if (p->Status2>0)
	  {
	  	cout << "MotionNotify " << rootx << " " << rooty << endl;
	  	p->mmoved=0;
	  }
	  else p->mmoved=1;
	  p->x=rootx;
	  p->y=rooty;
	  break;

	case KeyPress:
	  // a key was pressed
		DBG;
	  // should we stop looping, i.e. did the user press the quitkey?
	  if ( detail == p->QuitKey ) {
		// yep, no more loops
		cerr << "Got QuitKey, so exiting..." << endl;
		p->doit=0;
	  }
	  else {
		// send the keycode to the remote server
		if (p->mmoved)
		{
			cout << "MotionNotify " << p->x << " " << p->y << endl;
			p->mmoved=0;
		}
		cout << "KeyStrPress " << XKeysymToString(XKeycodeToKeysym(p->LocalDpy,detail,0)) << endl;

		p->ev.type = type;
		p->ev.xkey.type = type;
		p->ev.xkey.serial = seq;
		p->ev.xkey.send_event = (unsigned int)(ud1[0]>>8);
		p->ev.xkey.display=p->app->getDisplay();
		p->ev.xkey.state = kstate;
		p->ev.xkey.keycode = detail;
		p->ev.xkey.window = wevent;
		p->ev.xkey.root = wroot;
		p->ev.xkey.same_screen = samescreen;

		p->app->processEvent(p->ev);
	  }
	  break;

	case KeyRelease:
	  // a key was released
		DBG;
	  if (p->mmoved)
	  {
		cout << "MotionNotify " << p->x << " " << p->y << endl;
		p->mmoved=0;
	  }
	  cout << "KeyStrRelease " << XKeysymToString(XKeycodeToKeysym(p->LocalDpy,detail,0)) << endl;

		p->ev.type = type;
		p->ev.xkey.type = type;
		p->ev.xkey.serial = seq;
		p->ev.xkey.send_event = (unsigned int)(ud1[0]>>8);
		p->ev.xkey.display=p->app->getDisplay();
		p->ev.xkey.state = kstate;
		p->ev.xkey.keycode = detail;
		p->ev.xkey.window = wevent;
		p->ev.xkey.root = wroot;
		p->ev.xkey.same_screen = samescreen;

		p->app->processEvent(p->ev);
	  break;
  }
returning:
  XRecordFreeData(d);
}

/****************************************************************************/
/*! Main event-loop of the application. Loops until a key with the keycode
    \a QuitKey is pressed. Sends all mouse- and key-events to the remote
	display.

    \arg Display * LocalDpy - used display.
	\arg int LocalScreen - the used screen.
	\arg Display * RecDpy - used display.
	\arg unsigned int QuitKey - the key when pressed that quits the eventloop.
*/
/****************************************************************************/
void RecordAsyncNotify::run ()
{

	// TODO no arg
	Display * LocalDpy = localDisplay();
	int LocalScreen = 0;
	Display * RecDpy = localDisplay();
	unsigned int QuitKey = 0;

  Window       Root, rRoot, rChild;
  XRecordContext rc;
  XRecordRange *rr;
  XRecordClientSpec rcs;
  Priv         priv;
  int rootx, rooty, winx, winy;
  unsigned int mmask;
  Bool ret;
  Status sret;
  
  // get the root window and set default target
  Root = RootWindow ( LocalDpy, LocalScreen );

  ret=XQueryPointer(LocalDpy, Root, &rRoot, &rChild, &rootx, &rooty, &winx, &winy, &mmask);
  cerr << "XQueryPointer returned: " << ret << endl;
  rr=XRecordAllocRange();
  if (!rr)
  {
  	cerr << "Could not alloc record range, aborting." << endl;
  	exit(EXIT_FAILURE);
  }
  rr->device_events.first=KeyPress;
  rr->device_events.last=MotionNotify;
  rcs=XRecordAllClients;
  rc=XRecordCreateContext(RecDpy, 0, &rcs, 1, &rr, 1);
  if (!rc)
  {
  	cerr << "Could not create a record context, aborting." << endl;
  	exit(EXIT_FAILURE);
  }
  priv.x=rootx;
  priv.y=rooty;
  priv.mmoved=1;
  priv.Status2=0;
  priv.Status1=2;
  priv.doit=1;
  priv.QuitKey=QuitKey;
  priv.LocalDpy=LocalDpy;
  priv.RecDpy=RecDpy;
  priv.rc=rc;
  priv.app=&app;


  if (!XRecordEnableContextAsync(RecDpy, rc, eventCallback, (XPointer) &priv))
  {
  	cerr << "Could not enable the record context, aborting." << endl;
  	exit(EXIT_FAILURE);
  }

  while (!app.quit()) 
  {
	XRecordProcessReplies(RecDpy);
  }

  sret=XRecordDisableContext(LocalDpy, rc);
  if (!sret) cerr << "XRecordDisableContext failed!" << endl;
  sret=XRecordFreeContext(LocalDpy, rc);
  if (!sret) cerr << "XRecordFreeContext failed!" << endl;
  XFree(rr);
}


