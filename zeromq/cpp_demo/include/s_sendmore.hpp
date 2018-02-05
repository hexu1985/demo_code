#ifndef __ZHELPERS_S_SENDMORE_HPP_INCLUDED__
#define __ZHELPERS_S_SENDMORE_HPP_INCLUDED__

#include <string>
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

//  Sends string as 0MQ string, as multipart non-terminal
static bool
s_sendmore (zmq::socket_t & socket, const std::string & string) {

    zmq::message_t message(string.size());
    memcpy (message.data(), string.data(), string.size());

    bool rc = socket.send (message, ZMQ_SNDMORE);
    return (rc);
}

#endif
