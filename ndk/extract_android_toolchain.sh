#!/bin/sh

TARGET_DIR=$PWD/build/android-ndk-r14b
./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-aarch64 \
	--arch=arm64

./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-armv7 \
	--arch=arm

./android-ndk-r14b/build/tools/make-standalone-toolchain.sh \
	--platform=android-21 --install-dir=$TARGET_DIR/android-x86 \
	--arch=x86
