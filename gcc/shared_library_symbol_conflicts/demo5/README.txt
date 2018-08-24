Now re-introduce the worker to observe the conflict.

Compile, link, execute.

g++ -c main.cxx -o main.o
g++ -c work.cxx -o work.o
ar rc libmain.a main.o work.o
g++ -s -L. -o main.exe -lmain -lconflict

export LD_LIBRARY_PATH=.
./main.exe

start
work
layer
work
finished

Because work.o exists in libmain.a the DoThing() call from main() correctly executes from work.o, but surprisingly the DoThing() call from layer.o also executes from work.o instead of from conflict.o as might have been expected.
