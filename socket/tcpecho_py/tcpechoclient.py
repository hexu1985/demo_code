#!/usr/bin/env python
# UDP Example - Chapter 2

import socket, sys, time

host = sys.argv[1]
textport = sys.argv[2]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    port = int(textport)
except ValueError:
    # That didn't work.  Look it up instread.
    port = socket.getservbyname(textport, 'tcp')

s.connect((host, port))

while 1:
    data = sys.stdin.readline().strip()
    if not len(data):
        break
    s.sendall(data)
    buf = s.recv(2048)
    if not len(buf):
        break
    print "Received: %s" % buf

s.close()
