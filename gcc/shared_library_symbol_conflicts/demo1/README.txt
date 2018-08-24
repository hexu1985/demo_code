Compile the worker into an object file and wrap it as a static lib.

g++ -c work.cxx -o work.o
ar rc libwork.a work.o
Compile the application into an object file and wrap it as a static lib.

g++ -c main.cxx -o main.o
ar rc libmain.a main.o
Link the static libs into an executable. Note that the linker only looks further down the line when looking for symbols used by but not defined in the current lib. Thus the lowest level libs should go right-most and the left most symbol will be used when conflicts occur.

g++ -s -L. -o main.exe -lwork -lmain

./libmain.a(main.o): In function `main':
main.cxx:(.text+0x90): undefined reference to `DoThing()'
collect2: ld returned 1 exit status
Link successfully.

g++ -s -L. -o main.exe -lmain -lwork

./main.exe

start
work
finished
