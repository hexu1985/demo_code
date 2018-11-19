#!/usr/bin/env bash

/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -o main.exe main.cpp 
/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-objdump -D main.exe > main.dump

/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -o main_stack_protector_all.exe -fstack-protector-all main.cpp
/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-objdump -D main_stack_protector_all.exe > main_stack_protector_all.dump
