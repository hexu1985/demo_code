#ifndef __ZHELPERS_S_SET_ID_H_INCLUDED__
#define __ZHELPERS_S_SET_ID_H_INCLUDED__

#include <zmq.h>
#include <stdio.h>
#include "s_rand.h"

//  Set simple random printable identity on socket
//  Caution:
//    DO NOT call this version of s_set_id from multiple threads on MS Windows
//    since s_set_id will call rand() on MS Windows. rand(), however, is not 
//    reentrant or thread-safe. See issue #521.
static void
s_set_id (void *socket)
{
    char identity [10];
    sprintf (identity, "%04X-%04X", randof (0x10000), randof (0x10000));
    zmq_setsockopt (socket, ZMQ_IDENTITY, identity, strlen (identity));
}

#endif
