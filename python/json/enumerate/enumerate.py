#!/usr/bin/python
import json

filename = "maildata.json"

prop = json.load(open(filename))

#print(prop)

for key, value in prop.items():
    print("key: {}, value: {}".format(key, value))

