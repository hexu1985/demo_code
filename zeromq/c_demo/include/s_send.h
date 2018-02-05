#ifndef __ZHELPERS_S_SEND_H_INCLUDED__
#define __ZHELPERS_S_SEND_H_INCLUDED__

#include <zmq.h>
#include <string.h>

//  Convert C string to 0MQ string and send to socket
static int
s_send (void *socket, char *string) {
    int size = zmq_send (socket, string, strlen (string), 0);
    return size;
}

#endif
