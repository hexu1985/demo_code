#!/usr/bin/env python

import urllib2
import json

url = 'http://localhost:9000/demo'
data = { 'name':'hexu', 'age':32 }
headers = {'Content-Type': 'application/json'}

request = urllib2.Request(url=url, headers=headers, data=json.dumps(data))
response = urllib2.urlopen(request)

print "response: %s" % response.read()

