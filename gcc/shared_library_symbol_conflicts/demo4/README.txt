Now, introduce a new layer to call the conflict within the shared library.

g++ -c layer.cxx -o layer.o
Link the shared library.

g++ -shared layer.o conflict.o -o libconflict.so
And update the application to call they layer instead of calling the conflict directly.

Compile, link, execute.

g++ -c main.cxx -o main.o
ar rc libmain.a main.o
g++ -s -L. -o main.exe -lmain -lconflict

export LD_LIBRARY_PATH=.
./main.exe

start
layer
conflict
finished
