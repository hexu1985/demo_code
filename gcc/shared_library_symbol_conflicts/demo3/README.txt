Instead of a static library, package conflict as a shared library.

rm libconflict.a
g++ -shared conflict.o -o libconflict.so
Link for simple use of the shared library. In this case -lconflict refers to libconflict.so instead of libconflict.a

g++ -s -L. -o main.exe -lmain -lconflict

export LD_LIBRARY_PATH=.
./main.exe

start
conflict
finished
