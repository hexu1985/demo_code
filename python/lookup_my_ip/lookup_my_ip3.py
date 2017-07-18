#!/usr/bin/env python3
# Obtain Web Page - Chapter 6 - dump_page.py
import sys, urllib.request, re

req = urllib.request.Request('http://www.ip.cn/')
fd = urllib.request.urlopen(req)
res_page = str();
while 1:
    data = fd.read(1024)
    if not len(data):
        break
    res_page += str(data)

public_ip = ""
for line in res_page.split("\n"):
    match = re.match(".*<code>(.*)</code>.*", line)
    if match:
        public_ip = match.group(1)
        break

if len(public_ip):
    print("your public network ip is: %s" % public_ip)
else:
    print("sorry, not found your public network ip")

tmpstr=input("enter any key to continue")
