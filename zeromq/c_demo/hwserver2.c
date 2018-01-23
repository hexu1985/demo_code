// Hello World server
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (void)
{
    // Socket to talk to clients
    void *context = zmq_ctx_new ();

    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");

    assert (rc == 0);
    while (1) {
        zmq_msg_t request;
        zmq_msg_init(&request); 
        zmq_msg_recv (&request, responder, 0);
        printf ("Received Hello\n");
        zmq_msg_close(&request);

        sleep (1); // Do some 'work'

        zmq_msg_t reply;
        zmq_msg_init_size(&reply, 5);
        memcpy(zmq_msg_data(&reply), "World", 5);
        zmq_msg_send (&reply, responder, 0);
        zmq_msg_close(&reply);
    }

    zmq_close(responder);
    zmq_ctx_destroy(context);

    return 0;
}
