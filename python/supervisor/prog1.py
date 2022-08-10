#!/usr/bin/env python3

import sys
from time import sleep
from datetime import datetime

while True:
    print("{}: {}".format(sys.argv[0], datetime.now()))
    sleep(3.0)
