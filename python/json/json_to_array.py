#!/usr/bin/python
import json

beg_s = [1, 3, 5, 7, 9]
end_s = [2, 4, 6, 8, 10]

beg_s_jstr = "[1, 3, 5, 7, 9]" 
end_s_jstr = "[2, 4, 6, 8, 10]"
beg_s = json.loads(beg_s_jstr)
end_s = json.loads(end_s_jstr)

print("beg_s =", beg_s, ", end_s =", end_s)

