#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/extensions/record.h>
#include <X11/Xproto.h>

static void
callback(XPointer trash, XRecordInterceptData* data)
{
  printf("%d ", data->category);

      /*
  switch (data->category)
    {
    case XRecordStartOfData:
    case XRecordFromClient:
    case XRecordClientStarted:
    case XRecordClientDied:
    case XRecordEndOfData:
      break;
      */

  if (data->category == XRecordFromServer) {
    xEvent * event = (xEvent *)data->data;
    if (event->u.u.type == KeyPress) {
      printf("KeyPress");
    } else if (event->u.u.type == KeyRelease) {
      printf("KeyRelease");
    } else if (event->u.u.type == ButtonPress || event->u.u.type == ButtonRelease) {
      printf("ButtonPress/Release");
    } else if (event->u.u.type == MotionNotify) {
      printf("Motion");
    }
  } else if (data->category == XRecordStartOfData) {
    printf("Start of Data");
  }

  printf("\n");
  fflush(stdout);

  XRecordFreeData(data);
}

int
main()
{
  Display* display = XOpenDisplay(0);
  if (display == 0) {
    fprintf(stderr, "unable to open display\n");
    exit(-1);
  }

  int major, minor;

  if (!XRecordQueryVersion(display, &major, &minor)) {
    fprintf(stderr, "xrecord extension not available\n");
  }

  // Receive from ALL clients, including future clients.
  XRecordClientSpec clients = XRecordAllClients;
  XRecordRange* range = XRecordAllocRange();
  if (range == 0) {
    fprintf(stderr, "unable to allocate XRecordRange\n");
    exit(-1);
  }

  // Receive KeyPress, KeyRelease, ButtonPress, ButtonRelease and
  // MotionNotify events.
  memset(range, 0, sizeof(XRecordRange));
  range->device_events.first = KeyPress;
  range->device_events.last  = MotionNotify;
  // And create the XRECORD context.
  XRecordContext context = XRecordCreateContext (display, 0, &clients, 1, &range, 1);
  if (context == 0) {
    fprintf(stderr, "XRecordCreateContext failed\n");
    exit(-1);
  }
  XFree(range);

  // what is that for? (copied from workrave sourcecode)
  XSync(display, True);

  Display* display_datalink = XOpenDisplay(0);
  if (display_datalink == 0) {
    fprintf(stderr, "unable to open second display\n");
    exit(-1);
  }

  if (!XRecordEnableContext(display_datalink, context,  &callback, (XPointer)0)) {
    fprintf(stderr, "XRecordEnableContext() failed\n");
    exit(-1);
  }

  // Call above seems to block forever.
  fprintf(stderr, "Terminating. (huh?)\n");

  // Who cares about cleanup, linux and xorg sure will do this for us.
  return 0;
}
