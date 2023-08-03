#!/bin/bash

echo "FOO before test: $FOO"
FOO=${FOO:-"abc"}
echo "FOO after test: $FOO"
