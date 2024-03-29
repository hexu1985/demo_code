# Compile the worker into an object file and wrap it as a static lib.
g++ -c work.cpp -o work.o
ar rc libwork.a work.o

# Compile the application into an object file and wrap it as a static lib.
g++ -c main.cpp -o main.o
ar rc libmain.a main.o

# Compile the conflict into an object file and wrap it as a static lib.
g++ -c conflict.cpp -o conflict.o
ar rc libconflict.a conflict.o

g++ -s -L. -o main1.exe -lmain -lwork -lconflict
g++ -s -L. -o main2.exe -lmain -lconflict -lwork
