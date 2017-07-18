#!/usr/bin/env python3
# SMTP transmission with authentication - Chapter 10 - login.py

import sys, smtplib, socket
from getpass import getpass

if len(sys.argv) < 3:
    print("Syntax: %s self_ip toaddr [toaddr...]" % sys.argv[0])
    sys.exit(255)

self_ip = sys.argv[1]
toaddrs = sys.argv[2:]

server = "smtp.sina.com"
fromaddr = "arch_fangzhen_pc@sina.com"

message = """To: %s
From: %s
Subject: the arch_fangzhen_pc ip

Hello,
the arch_fangzhen_pc ip is %s

Good luck!
""" % (', '.join(toaddrs), fromaddr, self_ip)

username = "arch_fangzhen_pc@sina.com"
password = "1qaz2wsx3edc"

try:
    s = smtplib.SMTP(server)
    try:
        s.login(username, password)
    except smtplib.SMTPException as e:
        print("Authentication failed:", e)
        sys.exit(1)
    s.sendmail(fromaddr, toaddrs, message)
except (socket.gaierror, socket.error, socket.herror, smtplib.SMTPException) \
        as e:
    print(" *** Your message may not have been sent!")
    print(e)
    sys.exit(2)
else:
    print("Message successfully sent to %d recipient(s)" % len(toaddrs))

