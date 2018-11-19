#!/usr/bin/env bash

g++ -o main.exe main.cpp 
objdump -D main.exe > main.dump

g++ -o main_stack_protector.exe -fstack-protector main.cpp
objdump -D main_stack_protector.exe > main_stack_protector.dump

g++ -o main_stack_protector_all.exe -fstack-protector-all main.cpp
objdump -D main_stack_protector_all.exe > main_stack_protector_all.dump
