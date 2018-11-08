#!/usr/bin/env bash

clang++ -Wall  -o main.exe main.cpp
objdump -D main.exe > main.dump

/Users/hexu/obfuscator/bin/clang++ -Wall  -o main_ollvm.exe main.cpp
objdump -D main_ollvm.exe > main_ollvm.dump

/Users/hexu/obfuscator/bin/clang++ -Wall  -mllvm -fla -o main_ollvm_fla.exe main.cpp
objdump -D main_ollvm_fla.exe > main_ollvm_fla.dump

/Users/hexu/obfuscator/bin/clang++ -Wall  -mllvm -bcf -o main_ollvm_bcf.exe main.cpp
objdump -D main_ollvm_bcf.exe > main_ollvm_bcf.dump

/Users/hexu/obfuscator/bin/clang++ -Wall  -mllvm -sub -o main_ollvm_sub.exe main.cpp
objdump -D main_ollvm_sub.exe > main_ollvm_sub.dump
