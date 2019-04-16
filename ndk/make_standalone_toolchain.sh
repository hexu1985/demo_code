
TARGET_DIR=$PWD/android-ndk-r16b-clang-2
./android-ndk-r16b/build/tools/make_standalone_toolchain.py \
	--arch arm64 \
	--api 21 \
	--install-dir=$TARGET_DIR/android-aarch64

./android-ndk-r16b/build/tools/make_standalone_toolchain.py \
	--arch arm64 \
	--api 21 \
	--install-dir=$TARGET_DIR/android-armv7

./android-ndk-r16b/build/tools/make_standalone_toolchain.py \
	--arch arm64 \
	--api 21 \
	--install-dir=$TARGET_DIR/android-x86
