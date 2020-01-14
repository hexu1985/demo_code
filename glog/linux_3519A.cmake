# the name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR armv7)
set(HISI3519A 1)

set(_CMAKE_TOOLCHAIN_LOCATION /usr/local/toolchains/hisi-linux/arm-himix200-linux/bin)
set(_CMAKE_TOOLCHAIN_PREFIX arm-himix200-linux-)
set(CMAKE_C_COMPILER    ${_CMAKE_TOOLCHAIN_LOCATION}/${_CMAKE_TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER  ${_CMAKE_TOOLCHAIN_LOCATION}/${_CMAKE_TOOLCHAIN_PREFIX}g++)

# adjust the default behaviour of the find commands:
# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
