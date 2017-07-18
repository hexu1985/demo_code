#!/usr/bin/env python
# Obtain Web Page - Chapter 6 - dump_page.py
import sys, urllib2, re

def lookup_my_ip():
    req = urllib2.Request('http://www.ip.cn/')
    fd = urllib2.urlopen(req)
    res_page = str();
    while 1:
        data = fd.read(1024)
        if not len(data):
            break
        res_page += str(data)
    
    for line in res_page.split("\n"):
        match = re.match(".*<code>(.*)</code>.*", line)
        if match:
            return match.group(1)
    return ""

def test():
    public_ip = lookup_my_ip()
    if len(public_ip):
        print(public_ip)
    else:
        print("0.0.0.0")

if __name__ == '__main__':
    test()

