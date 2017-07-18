#!/usr/bin/env python
# usage: depends_on_analyse.py dir

import sys
import os
import re

debug = 1

# 遍历所有子目录, 把.h和.cpp文件存入列表中, 把.h文件存入字典中
def find_type_f(dir_name, file_list):
    if dir_name[-1] == '/':
        dir_name = dir_name[0:-1]
    for path in os.listdir(dir_name):
        abs_path = dir_name + '/' + path
        if (os.path.isfile(abs_path)):
            if (len(path) > 2 and path[-2:] == '.h') \
                    or (len(path) > 4 and path[-4:] == '.cpp'):
                file_list.append(abs_path)
        if (os.path.isdir(abs_path)):
            find_type_f(abs_path, file_list)

# 读取命令行参数
if debug:
    print("sys.argv: ", sys.argv, sep='')
    print("sys.argc: ", len(sys.argv), sep='')

if len(sys.argv) != 2:
    print("Usage:", sys.argv[0], "dir")
    raise SystemExit(1)

# 待遍历目录
dir_name = sys.argv[1]

# 遍历所有子目录, 把.h和.cpp文件存入列表中, 把.h文件存入字典中
file_list = list()
find_type_f(dir_name, file_list)

if debug:
    print("file_list------------------------")
    print(file_list)

# 打开所有.h和.cpp文件, 提取出#include部分, 以#include"xxx.h"中
# 的xxx.h为key, 以文件名为value, 插入字典
#print(file_list)



