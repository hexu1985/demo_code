#!/usr/bin/env bash

clang++ -Wall -o main.exe main_func.cpp
objdump -D main.exe > main.dump

/Users/hexu/obfuscator/bin/clang++ -Wall -o main_ollvm.exe main_func.cpp
objdump -D main_ollvm.exe > main_ollvm.dump

/Users/hexu/obfuscator/bin/clang++ -Wall -mllvm -fla -o main_ollvm_fla.exe main_func.cpp
objdump -D main_ollvm_fla.exe > main_ollvm_fla.dump

/Users/hexu/obfuscator/bin/clang++ -Wall -mllvm -bcf -o main_ollvm_bcf.exe main_func.cpp
objdump -D main_ollvm_bcf.exe > main_ollvm_bcf.dump

/Users/hexu/obfuscator/bin/clang++ -Wall -mllvm -sub -o main_ollvm_sub.exe main_func.cpp
objdump -D main_ollvm_sub.exe > main_ollvm_sub.dump

/Users/hexu/obfuscator/bin/clang++ -DUSE_BCF_OPT -Wall -o main_func_bcf.exe main_func.cpp
objdump -D main_func_bcf.exe > main_func_bcf.dump

/Users/hexu/obfuscator/bin/clang++ -DUSE_FLA_OPT -Wall -o main_func_fla.exe main_func.cpp
objdump -D main_func_fla.exe > main_func_fla.dump

/Users/hexu/obfuscator/bin/clang++ -DUSE_SUB_OPT -Wall -o main_func_sub.exe main_func.cpp
objdump -D main_func_sub.exe > main_func_sub.dump

/Users/hexu/obfuscator/bin/clang++ -DUSE_BCF_OPT -DUSE_FLA_OPT -Wall -o main_func_bcf_fla.exe main_func.cpp
objdump -D main_func_bcf_fla.exe > main_func_bcf_fla.dump

/Users/hexu/obfuscator/bin/clang++ -DUSE_FLA_OPT -DUSE_SUB_OPT -Wall -o main_func_fla_sub.exe main_func.cpp
objdump -D main_func_fla_sub.exe > main_func_fla_sub.dump

/Users/hexu/obfuscator/bin/clang++ -DUSE_BCF_OPT -DUSE_SUB_OPT -Wall -o main_func_bcf_sub.exe main_func.cpp
objdump -D main_func_bcf_sub.exe > main_func_bcf_sub.dump

/Users/hexu/obfuscator/bin/clang++ -DUSE_BCF_OPT -DUSE_FLA_OPT -DUSE_SUB_OPT -Wall -o main_func_bcf_fla_sub.exe main_func.cpp
objdump -D main_func_bcf_fla_sub.exe > main_func_bcf_fla_sub.dump
