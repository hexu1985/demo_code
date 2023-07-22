cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/local/google_benchmark
cmake --build build --target install --parallel 4 

