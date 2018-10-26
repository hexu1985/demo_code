#!/usr/bin/env bash

/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -o main.exe main.cpp
/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-objdump -D main.exe > main.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -o main_ollvm.exe main.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm.exe > main_ollvm.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -mllvm -fla -o main_ollvm_fla.exe main.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm_fla.exe > main_ollvm_fla.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -mllvm -bcf -o main_ollvm_bcf.exe main.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm_bcf.exe > main_ollvm_bcf.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -mllvm -sub -o main_ollvm_sub.exe main.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm_sub.exe > main_ollvm_sub.dump
