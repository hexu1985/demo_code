# Compile the application into an object file and wrap it as a static lib.
g++ -c main.cpp -o main.o
ar rc libmain.a main.o

# Compile the conflict into an object file and wrap it as a static lib.
g++ -fPIC -c conflict.cpp -o conflict.o
g++ -shared conflict.o -o libconflict.so

g++ -s -L. -o main.exe -lmain -lconflict
