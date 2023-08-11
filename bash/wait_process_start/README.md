### 等待进程启动

命令格式：wait_process_start.sh -p process_cmd_pattern [-t timeout_sec]
- p：等待启动的命令名（支持正则表达式）
- t：等待超时时间（单位秒）

返回结果：
- 0：被检测进程正常启动
- 非0：等待超时

示例1：
```
$ ./wait_process_start.sh -p nosuch
process_count: 0
process_count: 0
process_count: 0
not found nosuch
```

示例2：
```
$ sleep 30 &
[1] 18853
$ ./wait_process_start.sh -p sleep
process_count: 1
found sleep, count 1
```
