#ifndef __ZHELPERS_S_SENDMORE_H_INCLUDED__
#define __ZHELPERS_S_SENDMORE_H_INCLUDED__

#include <zmq.h>
#include <string.h>

//  Sends string as 0MQ string, as multipart non-terminal
static int
s_sendmore (void *socket, char *string) {
    int size = zmq_send (socket, string, strlen (string), ZMQ_SNDMORE);
    return size;
}

#endif
