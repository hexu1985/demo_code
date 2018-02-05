#ifndef __ZHELPERS_S_RECV_H_INCLUDED__
#define __ZHELPERS_S_RECV_H_INCLUDED__

#include <zmq.h>
#include <stdlib.h>
#include <string.h>

//  Receive 0MQ string from socket and convert into C string
//  Caller must free returned string. Returns NULL if the context
//  is being terminated.
static char *
s_recv (void *socket) {
    char buffer [256];
    int size = zmq_recv (socket, buffer, 255, 0);
    if (size == -1)
        return NULL;
    buffer[size] = '\0';

    char *dup = (char *) malloc(sizeof(buffer));
    if (dup == NULL)
        return NULL;
    memcpy(dup, buffer, sizeof(buffer));
    return dup;
}

#endif
