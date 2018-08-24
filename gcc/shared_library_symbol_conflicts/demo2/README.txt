Compile the conflict into an object file and wrap it as a static lib.

g++ -c conflict.cxx -o conflict.o
ar rc libconflict.a conflict.o
Link (without warning) with priority given to work.

g++ -s -L. -o main.exe -lmain -lwork -lconflict

./main.exe

start
work
finished
Link (without warning) with priority given to conflict.

g++ -s -L. -o main.exe -lmain -lconflict -lwork

./main.exe

start
conflict
finished
