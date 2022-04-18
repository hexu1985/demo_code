# osaccess_test.py

import os
import sys

if sys.argv[1] == '-n':
    file_name = sys.argv[2] # 从命令行获取文件名参数

if os.access(file_name, os.F_OK) is True:
    print ('File {} exists!'.format(file_name))
else:
    print ('File {} not exists!'.format(file_name))

if os.access(file_name, os.R_OK):
    print ('File {} can be read!'.format(file_name))
else:
    print ('File {} can not be read!'.format(file_name))

if os.access(file_name, os.W_OK):
    print ('File {} can be write!'.format(file_name))
else:
    print ('File {} can not be write!'.format(file_name))

if os.access(file_name, os.X_OK):
    print ('File {} can be executed!'.format(file_name))
else:
    print ('File {} can not be executed!'.format(file_name))

