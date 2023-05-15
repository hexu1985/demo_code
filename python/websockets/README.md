### virtualenv安装websockets

websockets依赖python的版本要大于等于3.7, 所以在
ubuntu18.04上需要安装python3.7或python3.8

更新软件包列表并安装必备组件：

```
$ sudo apt update
$ sudo apt install python3.8 python3.8-dev
```

通过键入以下命令验证安装是否成功

```
$ python3.8 --version
```
输出(视安装版本而定)：

3.8.16

安装websocktes:

```
$ python3.8 -m pip install  -i http://pypi.douban.com/simple --trusted-host pypi.douban.com websockets
```

