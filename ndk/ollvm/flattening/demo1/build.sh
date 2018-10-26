#!/usr/bin/env bash

/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -o main main.cpp
/opt/android-ndk-r14b-clang/android-aarch64/bin/aarch64-linux-android-objdump -D main > main.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -o main_ollvm main.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm > main_ollvm.dump

/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-clang++ -Wall -fPIE -pie -mllvm -fla -o main_ollvm_fla main.cpp
/opt/android-ndk-r14b-ollvm/android-aarch64/bin/aarch64-linux-android-objdump -D main_ollvm_fla > main_ollvm_fla.dump
