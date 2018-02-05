#ifndef __ZHELPERS_S_SEND_HPP_INCLUDED__
#define __ZHELPERS_S_SEND_HPP_INCLUDED__

#include <string>
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

//  Convert string to 0MQ string and send to socket
static bool
s_send (zmq::socket_t & socket, const std::string & string) {

    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message);
    return (rc);
}

#endif
