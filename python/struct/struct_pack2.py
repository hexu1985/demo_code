#!/usr/bin/env python

import struct
import binascii

values = (1, 'ab', 2.7)
packed_data = struct.pack('I 2s f', *values)
print 'Original values:', values
print 'Packed Value   :', binascii.hexlify(packed_data)

