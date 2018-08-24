# Compile the worker into an object file and wrap it as a static lib.
g++ -c work.cpp -o work.o
ar rc libwork.a work.o

# Compile the application into an object file and wrap it as a static lib.
g++ -c main.cpp -o main.o
ar rc libmain.a main.o

g++ -s -L. -o main.exe -lmain -lwork
