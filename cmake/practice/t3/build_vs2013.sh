cmake -G "Visual Studio 12 Win64" -T "v120_xp" -Bbuild -H. -DCMAKE_INSTALL_PREFIX="E:\tmp\lib\vs2013"
cmake --build build/ --target install
