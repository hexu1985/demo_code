#!/usr/bin/env python
# UDP Example - Chapter 2

import socket, sys, time

if len(sys.argv) < 3:
    print "usage: udpechoclient01.py <hostname> <service> [localip]"
    sys.exit(1)

host = sys.argv[1]
textport = sys.argv[2]

if len(sys.argv) == 4:
    local_ip = sys.argv[3]
else:
    local_ip = ''

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((local_ip, 0))

try:
    port = int(textport)
except ValueError:
    # That didn't work.  Look it up instread.
    port = socket.getservbyname(textport, 'udp')

s.connect((host, port))
print "Looking for replies; press Ctrl-C or Ctrl-Break to stop."
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
