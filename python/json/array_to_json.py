#!/usr/bin/python
import json

beg_s = [1, 3, 5, 7, 9]
end_s = [2, 4, 6, 8, 10]

beg_s_jstr = json.dumps(beg_s)
end_s_jstr = json.dumps(end_s)
print('--beg_s "{}" --end_s "{}"'.format(beg_s_jstr, end_s_jstr))

