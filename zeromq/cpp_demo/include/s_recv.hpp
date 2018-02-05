#ifndef __ZHELPERS_S_RECV_HPP_INCLUDED__
#define __ZHELPERS_S_RECV_HPP_INCLUDED__

#include <string>
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

//  Receive 0MQ string from socket and convert into string
static std::string
s_recv (zmq::socket_t & socket) {

    zmq::message_t message;
    socket.recv(&message);

    return std::string(static_cast<char*>(message.data()), message.size());
}

#endif
