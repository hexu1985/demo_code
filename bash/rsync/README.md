rsync 命令的基本格式有多种，分别是：

```
[root@localhost ~]# rsync [OPTION] SRC DEST
[root@localhost ~]# rsync [OPTION] SRC [USER@]HOST:DEST
[root@localhost ~]# rsync [OPTION] [USER@]HOST:SRC DEST
[root@localhost ~]# rsync [OPTION] [USER@]HOST::SRC DEST
[root@localhost ~]# rsync [OPTION] SRC [USER@]HOST::DEST
```
针对以上 5 种命令格式，rsync 有 5 种不同的工作模式：

- 第一种用于仅在本地备份数据；
- 第二种用于将本地数据备份到远程机器上；
- 第三种用于将远程机器上的数据备份到本地机器上；
- 第四种和第三种是相对的，同样第五种和第二种是相对的，它们各自之间的区别在于登陆认证时使用的验证方式不同。

| OPTION选项 | 	功能|
| ---------- | ---- |
| -a 	| 这是归档模式，表示以递归方式传输文件，并保持所有属性，它等同于-r、-l、-p、-t、-g、-o、-D 选项。-a 选项后面可以跟一个 --no-OPTION，表示关闭 -r、-l、-p、-t、-g、-o、-D 中的某一个，比如-a --no-l 等同于 -r、-p、-t、-g、-o、-D 选项。|
| -r 	| 表示以递归模式处理子目录，它主要是针对目录来说的，如果单独传一个文件不需要加 -r 选项，但是传输目录时必须加。|
| -v 	| 表示打印一些信息，比如文件列表、文件数量等。|
| -l 	| 表示保留软连接。|
| -L 	| 表示像对待常规文件一样处理软连接。如果是 SRC 中有软连接文件，则加上该选项后，将会把软连接指向的目标文件复制到 DEST。|
| -p 	| 表示保持文件权限。|
| -o 	| 表示保持文件属主信息。|
| -g 	| 表示保持文件属组信息。|
| -D 	| 表示保持设备文件信息。|
| -t 	| 表示保持文件时间信息。|
| --delete	| 表示删除 DEST 中 SRC 没有的文件。|
| --exclude=PATTERN 	| 表示指定排除不需要传输的文件，等号后面跟文件名，可以是通配符模式（如 *.txt）。|
| --progress |	表示在同步的过程中可以看到同步的过程状态，比如统计要同步的文件数量、 同步的文件传输速度等。|
| -u 	| 表示把 DEST 中比 SRC 还新的文件排除掉，不会覆盖。|
| -z 	| 加上该选项，将会在传输过程中压缩。|

举例:
```
$ rsync -avP hexu@10.0.0.11:/home/hexu/test.txt .
```
