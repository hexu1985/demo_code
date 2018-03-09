#ifndef __ZHELPERS_S_DUMP_H_INCLUDED__
#define __ZHELPERS_S_DUMP_H_INCLUDED__

#include <zmq.h>
#include <assert.h>
#include <string.h>

//  Receives all message parts from socket, prints neatly
//
static void
s_dump (void *socket)
{
    int rc;

    zmq_msg_t message;
    rc = zmq_msg_init (&message);
    assert (rc == 0);

    puts ("----------------------------------------");
    //  Process all parts of the message
    do {
        int size = zmq_msg_recv (&message, socket, 0);
        assert (size >= 0);

        //  Dump the message as text or binary
        char *data = (char*)zmq_msg_data (&message);
        assert (data != 0);
        int is_text = 1;
        int char_nbr;
        for (char_nbr = 0; char_nbr < size; char_nbr++) {
            if ((unsigned char) data [char_nbr] < 32
                || (unsigned char) data [char_nbr] > 126) {
                is_text = 0;
            }
        }

        printf ("[%03d] ", size);
        for (char_nbr = 0; char_nbr < size; char_nbr++) {
            if (is_text) {
                printf ("%c", data [char_nbr]);
            } else {
                printf ("%02X", (unsigned char) data [char_nbr]);
            }
        }
        printf ("\n");
    } while (zmq_msg_more (&message));

    rc = zmq_msg_close (&message);
    assert (rc == 0);
}

#endif
