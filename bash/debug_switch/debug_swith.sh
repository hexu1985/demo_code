#!/bin/bash

debug=2

echo "info 1"
((debug>=1)) && echo "debug level 1: messag 1"
echo "info 2"
((debug>=2)) && echo "debug level messag 2"
