#!/bin/sh

TARGET_DIR=$PWD/build/android-ndk-r14b-clang
./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-aarch64 \
	--arch=arm64 --toolchain=aarch64-linux-androideabi-clang --stl=libc++

./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-armv7 \
	--arch=arm --toolchain=arm-linux-androideabi-clang --stl=libc++

./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-x86 \
	--arch=x86 --toolchain=x86-linux-androideabi-clang --stl=libc++
