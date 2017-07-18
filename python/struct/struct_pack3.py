#!/usr/bin/env python

import sys
import struct
import binascii

v1 = int(sys.argv[1])
v2 = int(sys.argv[2])
v3 = int(sys.argv[3])
packed_data = struct.pack('! B B H', v1, v2, v3)
print 'Original values:', v1, v2, v3
print 'Packed Value   :', binascii.hexlify(packed_data)

