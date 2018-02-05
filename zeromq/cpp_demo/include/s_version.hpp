#ifndef __ZHELPERS_S_VERSION_HPP_INCLUDED__
#define __ZHELPERS_S_VERSION_HPP_INCLUDED__

#include <iostream>
#include <zmq.hpp> // https://github.com/zeromq/cppzmq

//  Report 0MQ version number
//
static void
s_version (void)
{
    int major, minor, patch;
    zmq_version (&major, &minor, &patch);
    std::cout << "Current 0MQ version is " << major << "." << minor << "." << patch << std::endl;
}

#endif
