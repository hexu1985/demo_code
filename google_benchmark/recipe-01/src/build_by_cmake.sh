#!/usr/bin/env bash

cd `dirname ${BASH_SOURCE[0]}`
cmake -H. -Bbuild -Dbenchmark_DIR=~/local/google_benchmark/lib/cmake/benchmark
VERBOSE=1 cmake --build build
echo "target dir is build"
