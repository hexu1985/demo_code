#!/usr/bin/env python3
import os
import sys
import json

has_test_file = False
test_file = "test.json"
test_cmake = "test.cmake"

def generate_cmake_list(list_name, var_list):
    return "set("+list_name+" "+" ".join(var_list)+")"

if os.access(test_file, os.F_OK):
    has_test_file = True

if (not has_test_file):
    print("delete", test_cmake)
    sys.exit(1)

print("has_test_file:", has_test_file)

with open(test_file) as f:
    test_map = json.load(f)

item_list = test_map["menu"]["item_list"]

with open(test_cmake, "w") as f:
    print(generate_cmake_list("item_list", item_list), file=f)
    print("message(\"in test.cmake, item_list: ${item_list}\")", file=f)

