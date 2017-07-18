#!/usr/bin/env python
# UDP Echo Server - Chapter 3 - udpechoserver.py
import socket, traceback
import sys

if len(sys.argv) != 3:
    print "usage: udpechoserver02.py <hostname> <service>"
    sys.exit(1)

host = sys.argv[1]
port = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))

while 1:
    try:
        message, address = s.recvfrom(8192)
        print "Got data from %s: %s" % (address, message)
        # Echo it back
        s.sendto(message, address)
    except (KeyboardInterrupt, SystemExit):
        raise
    except:
        traceback.print_exc()

