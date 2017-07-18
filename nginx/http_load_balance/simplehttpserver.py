#!/usr/bin/env python

import sys
import SimpleHTTPServer
import SocketServer

if len(sys.argv) != 3:
    print "usage: udpechoserver02.py <hostname> <service>"
    sys.exit(1)

host = sys.argv[1]                               # Bind to all interfaces
port = int(sys.argv[2])

Handler = SimpleHTTPServer.SimpleHTTPRequestHandler

httpd = SocketServer.TCPServer((host, port), Handler)

print "serving at %s:%d" % (host, port)
httpd.serve_forever()
