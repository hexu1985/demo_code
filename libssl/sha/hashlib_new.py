#!/usr/bin/env python
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""Naming the hash type using a string.
"""

__version__ = "$Id$"
#end_pymotw_header

import hashlib
import sys

if len(sys.argv) != 3:
    print "usage: %s sha-name data" % sys.argv[0]
    sys.exit(1)

hash_name = sys.argv[1]
data = sys.argv[2]
h = hashlib.new(hash_name)
h.update(data)
print h.hexdigest()

