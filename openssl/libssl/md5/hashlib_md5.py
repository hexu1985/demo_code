#!/usr/bin/env python
# encoding: utf-8
#
# Copyright (c) 2008 Doug Hellmann All rights reserved.
#
"""Simple MD5 generation.
"""

__version__ = "$Id$"
#end_pymotw_header

import hashlib
import sys

if len(sys.argv) != 2:
    print "usage: %s str" % sys.argv[0]
    sys.exit(1)

lorem = sys.argv[1]

h = hashlib.md5()
h.update(lorem)
print h.hexdigest()
