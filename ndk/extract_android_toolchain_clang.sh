#!/bin/sh

TARGET_DIR=/opt/android-ndk-r14b-clang
./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-aarch64 \
	--arch=arm64 --toolchain=arm-linux-androideabi-clang --stl=libc++

./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-armv7_16 \
	--arch=arm --toolchain=arm-linux-androideabi-clang --stl=libc++

./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-x86 \
	--arch=x86 --toolchain=arm-linux-androideabi-clang --stl=libc++
