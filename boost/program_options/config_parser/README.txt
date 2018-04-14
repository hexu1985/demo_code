ConfigParser说明:
1) parse_command_line: 对于无效的命令行参数, 会抛出异常, 支持长短参数的时候, 用','分隔符, 但不能有空格
2) parse_config_file: 解析文件中碰到无效的参数, 解析就会终止
3) parse_environment: 通过环境变量名映射, 查找对应的参数
4) 解析是按照insert方式插入到variables_map中的, 所以优先级高的应该放在前面调用 
