#!/bin/sh

END_INDEX=76
BEGIN_INDEX=1
OUT_DIR=ft-20150309

page_index=$BEG_INDEX
while (( page_index < END_INDEX ))
do
  wget -O ${OUT_DIR}/N${page_index}.html "http://bj.esf.sina.com.cn/house/a7-b20-c100,200-d50,100-k1-n${page_index}/"
  (( page_index += 1 ))
done
