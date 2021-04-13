import sys

f=open(sys.argv[1])
a=f.read()
for x in a.split():
    print(x)

