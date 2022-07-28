#!/usr/bin/env python3

import requests

r = requests.get('http://localhost:5000/')
print(r.text)
