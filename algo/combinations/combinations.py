#!/usr/bin/env python3

import itertools
import sys

# example: combinations.py 3 a b c d 
if (len(sys.argv) < 2 or int(sys.argv[1]) > len(sys.argv)-2):
    print("usage: {} num item1 [item2] ....".format(sys.argv[0]))
    sys.exit(1)

select_num = int(sys.argv[1]);
origin_set = sys.argv[2:]
print("combinations {} from set: {}".format(select_num, ' '.join(origin_set)));

int_set = range(0, len(origin_set));

for combination_idx in itertools.combinations(int_set, select_num):
    for i in combination_idx:
        print(origin_set[i], end=' ')
    print()
