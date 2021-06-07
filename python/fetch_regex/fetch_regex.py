import re
import sys

pattern = None

if len(sys.argv) > 1:
    pattern = sys.argv[1]
else:
    print("Usage: {} pattern".format(sys.argv[0]))
    sys.exit(-1)

f = open("tmp.txt")

str_list=[]

for line in f:
    str_list += re.findall(pattern, line)
    
str_set=set(str_list)
for v in str_set:
    print(v)
