#!/usr/bin/env bash

/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -o main.exe main_func.cpp
/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-objdump -D main.exe > main.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -o main_ollvm.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm.exe > main_ollvm.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -mllvm -fla -o main_ollvm_fla.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm_fla.exe > main_ollvm_fla.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -mllvm -bcf -o main_ollvm_bcf.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm_bcf.exe > main_ollvm_bcf.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -mllvm -sub -o main_ollvm_sub.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm_sub.exe > main_ollvm_sub.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -DUSE_BCF_OPT -Wall -fPIE -pie -o main_func_bcf.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_func_bcf.exe > main_func_bcf.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -DUSE_FLA_OPT -Wall -fPIE -pie -o main_func_fla.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_func_fla.exe > main_func_fla.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -DUSE_SUB_OPT -Wall -fPIE -pie -o main_func_sub.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_func_sub.exe > main_func_sub.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -DUSE_BCF_OPT -DUSE_FLA_OPT -Wall -fPIE -pie -o main_func_bcf_fla.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_func_bcf_fla.exe > main_func_bcf_fla.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -DUSE_FLA_OPT -DUSE_SUB_OPT -Wall -fPIE -pie -o main_func_fla_sub.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_func_fla_sub.exe > main_func_fla_sub.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -DUSE_BCF_OPT -DUSE_SUB_OPT -Wall -fPIE -pie -o main_func_bcf_sub.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_func_bcf_sub.exe > main_func_bcf_sub.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -DUSE_BCF_OPT -DUSE_FLA_OPT -DUSE_SUB_OPT -Wall -fPIE -pie -o main_func_bcf_fla_sub.exe main_func.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_func_bcf_fla_sub.exe > main_func_bcf_fla_sub.dump
