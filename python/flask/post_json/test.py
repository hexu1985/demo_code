#!/usr/bin/env python3

import json
import requests

url = 'http://localhost:5000/post_test'
d = {'key1': 'value1', 'key2': 'value2'}
r = requests.post(url, data=json.dumps(d))
print(r.status_code)
print(r.text)
print(json.loads(r.text))
