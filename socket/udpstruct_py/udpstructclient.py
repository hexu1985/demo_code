#!/usr/bin/env python
# UDP Example - Chapter 2

import socket, sys, time
import struct

host = sys.argv[1]
textport = sys.argv[2]

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
try:
    port = int(textport)
except ValueError:
    # That didn't work.  Look it up instread.
    port = socket.getservbyname(textport, 'udp')

s.connect((host, port))

req_format = "!h b h"

v1 = 12
v2 = 2
v3 = 24

ret = 0

st = struct.Struct(req_format)
packed_data = st.pack(v1, v2, v3)

while 1:
    s.sendall(packed_data)
    buf = s.recv(2048)
    if not len(buf):
        break
    st = struct.Struct("!h")
    unpacked_data = st.unpack(buf)
    print "Received: buf(%s), unpacked_data(%s)" % (buf, unpacked_data)
    break

s.close()
