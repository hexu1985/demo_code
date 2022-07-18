#!/usr/bin/env python3
# encoding: utf-8
#
# Copyright (c) 2009 Doug Hellmann All rights reserved.
#
"""
"""

#end_pymotw_header
import collections

def test():
    Camera = collections.namedtuple('Camera', 'id type index')
    
    camera1 = Camera(id='usb_0', type='vcm', index='0')
    print('\nRepresentation:', camera1)
    
    camera2 = Camera(id='xdma_0', type='fpga', index='3')
    print('\nField by id:', camera2.id)
    
    print('\nFields by index:')
    for p in [camera1, camera2]:
        print('{}: type {}, index {}'.format(*p))

test()
