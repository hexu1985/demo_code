#!/usr/bin/env bash
./filter_email.py test.data | sort | uniq >& emails.txt
echo "see the emails.txt for result"

